#ifndef SHANNONFANO_H
#define SHANNONFANO_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <iostream>

struct CharStat {
	unsigned int symbol{};
	long long count{};
	std::string bin_code;

	CharStat(unsigned int s, long long c) : symbol(s), count(c) {}

	bool operator>(const CharStat& o) const {
		return count > o.count;
	}
};

class ShannonCompressor {
	std::vector<CharStat> stats;
	std::map<unsigned int, std::string> encode_map;
	std::map<std::string, unsigned int> decode_map;

	void make_codes(int left, int right);

	unsigned int get_next_char(const std::string& s, size_t& p);
	std::string to_utf8(unsigned int cp);

	static void write_bits(std::ofstream& out, const std::string& bits);
	static std::string read_bits(std::ifstream& in, unsigned long long bit_count);

public:
	bool run_encoding(const std::string& in_file, const std::string& out_file);
	bool run_decoding(const std::string& in_file, const std::string& out_file);

	void print_table();
};

#endif // SHANNONFANO_H