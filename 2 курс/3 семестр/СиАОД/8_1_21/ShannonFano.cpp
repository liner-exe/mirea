#include "ShannonFano.h"

unsigned int ShannonCompressor::get_next_char(const std::string& s, size_t& p) {
    unsigned char b1 = static_cast<unsigned char>(s[p]);

    if (b1 < 0x80) {
        p += 1;
        return b1;
    }

    if ((b1 & 0xE0) == 0xC0) {
        unsigned int res =
            ((b1 & 0x1F) << 6) |
            (static_cast<unsigned char>(s[p + 1]) & 0x3F);
        p += 2;
        return res;
    }

    if ((b1 & 0xF0) == 0xE0) {
        unsigned int res =
            ((b1 & 0x0F) << 12) |
            ((static_cast<unsigned char>(s[p + 1]) & 0x3F) << 6) |
            (static_cast<unsigned char>(s[p + 2]) & 0x3F);
        p += 3;
        return res;
    }

    if ((b1 & 0xF8) == 0xF0) {
        unsigned int res =
            ((b1 & 0x07) << 18) |
            ((static_cast<unsigned char>(s[p + 1]) & 0x3F) << 12) |
            ((static_cast<unsigned char>(s[p + 2]) & 0x3F) << 6) |
            (static_cast<unsigned char>(s[p + 3]) & 0x3F);
        p += 4;
        return res;
    }

    p++;
    return 0;
}

std::string ShannonCompressor::to_utf8(unsigned int cp) {
    std::string res;

    if (cp <= 0x7F) {
        res += char(cp);
    } else if (cp <= 0x7FF) {
        res += char(0xC0 | (cp >> 6));
        res += char(0x80 | (cp & 0x3F));
    } else if (cp <= 0xFFFF) {
        res += char(0xE0 | (cp >> 12));
        res += char(0x80 | ((cp >> 6) & 0x3F));
        res += char(0x80 | (cp & 0x3F));
    } else {
        res += char(0xF0 | (cp >> 18));
        res += char(0x80 | ((cp >> 12) & 0x3F));
        res += char(0x80 | ((cp >> 6) & 0x3F));
        res += char(0x80 | (cp & 0x3F));
    }

    return res;
}

void ShannonCompressor::make_codes(int left, int right) {
    if (left == right) return;

    long long total = 0;
    for (int i = left; i <= right; ++i)
        total += stats[i].count;

    long long cur = 0;
    int sep = left;
    long long best = LLONG_MAX;

    for (int i = left; i < right; ++i) {
        cur += stats[i].count;
        long long diff = llabs(total - 2 * cur);
        if (diff < best) {
            best = diff;
            sep = i;
        }
    }

    for (int i = left; i <= sep; ++i) stats[i].bin_code.push_back('0');
    for (int i = sep + 1; i <= right; ++i) stats[i].bin_code.push_back('1');

    make_codes(left, sep);
    make_codes(sep + 1, right);
}

void ShannonCompressor::write_bits(std::ofstream& out, const std::string& bits) {
    unsigned char byte = 0;
    int cnt = 0;

    for (char b : bits) {
        byte <<= 1;
        if (b == '1') byte |= 1;
        cnt++;

        if (cnt == 8) {
            out.put(byte);
            cnt = 0;
            byte = 0;
        }
    }

    if (cnt) {
        byte <<= (8 - cnt);
        out.put(byte);
    }
}

std::string ShannonCompressor::read_bits(std::ifstream& in, unsigned long long bit_count) {
    std::string bits;
    bits.reserve(bit_count);

    while (bit_count > 0) {
        unsigned char byte = 0;
        if (!in.read(reinterpret_cast<char*>(&byte), 1)) break;

        for (int i = 7; i >= 0 && bit_count > 0; --i) {
            bits.push_back(((byte >> i) & 1) ? '1' : '0');
            bit_count--;
        }
    }
    return bits;
}

void ShannonCompressor::print_table() {
    std::cout << std::endl << "Таблица кодирования" << std::endl;
    for (auto& s : stats) {
        std::string visual = to_utf8(s.symbol);
        if (visual == " ") visual = "' '";
        std::cout << visual << "\t| " << s.count << "\t| " << s.bin_code << std::endl;
    }
}

bool ShannonCompressor::run_encoding(const std::string& in_file, const std::string& out_file) {

    std::ifstream f_in(in_file, std::ios::binary);
    if (!f_in) return false;

    std::string content((std::istreambuf_iterator<char>(f_in)),
                         std::istreambuf_iterator<char>());
    f_in.close();

    if (content.empty()) {
        std::ofstream out(out_file, std::ios::binary);
        unsigned char mode = 1;
        out.write((char*)&mode, 1);
        return true;
    }

    std::map<unsigned int, long long> freq;
    size_t pos = 0;

    while (pos < content.size()) {
        unsigned int ch = get_next_char(content, pos);
        if (ch) freq[ch]++;
    }

    stats.clear();
    for (auto &p : freq) stats.emplace_back(p.first, p.second);

    std::sort(stats.begin(), stats.end(), std::greater<CharStat>());

    make_codes(0, (int)stats.size() - 1);

    encode_map.clear();
    decode_map.clear();

    for (auto &s : stats) {
        encode_map[s.symbol] = s.bin_code;
        decode_map[s.bin_code] = s.symbol;
    }

    std::string bit_stream;
    pos = 0;
    while (pos < content.size()) {
        unsigned int ch = get_next_char(content, pos);
        bit_stream += encode_map[ch];
    }

    unsigned long long total_bits = bit_stream.size();

    size_t estimated = 1 + 4 + stats.size() * (4 + 1) + 8 + (total_bits + 7) / 8;
    for (auto &s : stats)
        estimated += (s.bin_code.size() + 7) / 8;

    size_t original = content.size();

    std::ofstream out(out_file, std::ios::binary);

    if (estimated >= original) {
        unsigned char mode = 1;
        out.write((char*)&mode, 1);
        out.write(content.data(), content.size());
        return true;
    }

    unsigned char mode = 0;
    out.write((char*)&mode, 1);

    unsigned int sz = stats.size();
    out.write((char*)&sz, 4);

    for (auto &s : stats) {

        out.write((char*)&s.symbol, 4);

        unsigned char len = (unsigned char)s.bin_code.size();
        out.write((char*)&len, 1);

        write_bits(out, s.bin_code);
    }

    out.write((char*)&total_bits, 8);

    write_bits(out, bit_stream);

    return true;
}

bool ShannonCompressor::run_decoding(const std::string& in_file, const std::string& out_file) {

    std::ifstream in(in_file, std::ios::binary);
    if (!in) return false;

    unsigned char mode = 0;
    in.read((char*)&mode, 1);

    if (mode == 1) {
        std::ofstream out(out_file, std::ios::binary);
        out << in.rdbuf();
        return true;
    }

    stats.clear();
    decode_map.clear();

    unsigned int sz = 0;
    in.read((char*)&sz, 4);

    for (unsigned int i = 0; i < sz; ++i) {

        unsigned int sym;
        unsigned char len;

        in.read((char*)&sym, 4);
        in.read((char*)&len, 1);

        std::string bits = read_bits(in, len);

        stats.emplace_back(sym, 0);
        stats.back().bin_code = bits;

        decode_map[bits] = sym;
    }

    unsigned long long total_bits = 0;
    in.read((char*)&total_bits, 8);

    std::string bits = read_bits(in, total_bits);

    std::ofstream out(out_file, std::ios::binary);

    std::string cur;
    for (char b : bits) {
        cur.push_back(b);
        auto it = decode_map.find(cur);
        if (it != decode_map.end()) {
            out << to_utf8(it->second);
            cur.clear();
        }
    }

    return true;
}
