#include "Huffman.h"

HuffmanNode::HuffmanNode(std::string d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}

bool HuffmanNode::isLeaf() const
{
    return left == nullptr && right == nullptr;
}

bool CompareNode::operator()(const std::shared_ptr<HuffmanNode> &a,
                             const std::shared_ptr<HuffmanNode> &b) const
{
    return a->frequency > b->frequency;
}

void HuffmanCoder::countFrequencies(const std::string &text)
{
    frequency.clear();
    for (size_t i = 0; i < text.length();)
    {
        unsigned char c = text[i];
        int charLength = 0;
        if ((c & 0x80) == 0)
            charLength = 1;
        else if ((c & 0xE0) == 0xC0)
            charLength = 2;
        else if ((c & 0xF0) == 0xE0)
            charLength = 3;
        else if ((c & 0xF8) == 0xF0)
            charLength = 4;
        else { i++; continue; }

        std::string symbol = text.substr(i, charLength);
        frequency[symbol]++;
        i += charLength;
    }
}

void HuffmanCoder::buildHuffmanTree()
{
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareNode> minHeap;

    for (const auto &p : frequency)
        minHeap.push(std::make_shared<HuffmanNode>(p.first, p.second));

    while (minHeap.size() > 1)
    {
        auto left = minHeap.top(); minHeap.pop();
        auto right = minHeap.top(); minHeap.pop();

        auto node = std::make_shared<HuffmanNode>("", left->frequency + right->frequency);
        node->left = left;
        node->right = right;
        minHeap.push(node);
    }

    if (!minHeap.empty())
        root = minHeap.top();
}

void HuffmanCoder::generateCodes(std::shared_ptr<HuffmanNode> node, const std::string &code)
{
    if (!node) return;
    if (node->isLeaf()) { huffmanCodes[node->data] = code; return; }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

std::string HuffmanCoder::serializeTree(std::shared_ptr<HuffmanNode> node)
{
    if (!node) return "";
    if (node->isLeaf()) return "1" + node->data;
    return "0" + serializeTree(node->left) + serializeTree(node->right);
}

std::shared_ptr<HuffmanNode> HuffmanCoder::deserializeTree(const std::string &serialized, size_t &pos)
{
    if (pos >= serialized.length()) return nullptr;

    if (serialized[pos] == '1')
    {
        pos++;
        unsigned char c = serialized[pos];
        int len = 0;
        if ((c & 0x80) == 0) len = 1;
        else if ((c & 0xE0) == 0xC0) len = 2;
        else if ((c & 0xF0) == 0xE0) len = 3;
        else if ((c & 0xF8) == 0xF0) len = 4;

        std::string symbol = serialized.substr(pos, len);
        pos += len;
        return std::make_shared<HuffmanNode>(symbol, 0);
    }

    pos++;
    auto node = std::make_shared<HuffmanNode>("", 0);
    node->left = deserializeTree(serialized, pos);
    node->right = deserializeTree(serialized, pos);
    return node;
}

std::string HuffmanCoder::compress(const std::string &text)
{
    countFrequencies(text);
    buildHuffmanTree();
    huffmanCodes.clear();
    if (root) generateCodes(root, "");

    std::string compressedBits;
    for (size_t i = 0; i < text.length();)
    {
        unsigned char c = text[i];
        int len = 0;
        if ((c & 0x80) == 0) len = 1;
        else if ((c & 0xE0) == 0xC0) len = 2;
        else if ((c & 0xF0) == 0xE0) len = 3;
        else if ((c & 0xF8) == 0xF0) len = 4;
        else { i++; continue; }

        std::string symbol = text.substr(i, len);
        compressedBits += huffmanCodes[symbol];
        i += len;
    }

    std::string serializedTree = serializeTree(root);
    std::string compressed;

    unsigned int treeLen = serializedTree.length();
    compressed.append(reinterpret_cast<char *>(&treeLen), 4);
    compressed += serializedTree;

    unsigned int bitsLen = compressedBits.length();
    compressed.append(reinterpret_cast<char *>(&bitsLen), 4);

    for (size_t i = 0; i < compressedBits.length(); i += 8)
    {
        std::bitset<8> byte;
        for (size_t j = 0; j < 8; j++)
            if (i + j < compressedBits.length()) byte[7 - j] = (compressedBits[i + j] == '1');
        compressed += static_cast<char>(byte.to_ulong());
    }

    return compressed;
}

std::string HuffmanCoder::decompress(const std::string &compressedData)
{
    if (compressedData.length() < 8) return "";

    unsigned int treeLen; memcpy(&treeLen, compressedData.data(), 4);
    std::string serializedTree = compressedData.substr(4, treeLen);
    size_t pos = 0; root = deserializeTree(serializedTree, pos);

    unsigned int bitsLen; memcpy(&bitsLen, compressedData.data() + 4 + treeLen, 4);
    const char *dataStart = compressedData.data() + 8 + treeLen;
    size_t dataBytes = (bitsLen + 7) / 8;

    std::string compressedBits;
    for (size_t i = 0; i < dataBytes; i++)
    {
        std::bitset<8> byte(dataStart[i]);
        for (int j = 7; j >= 0; j--)
            if (compressedBits.length() < bitsLen) compressedBits += byte[j] ? '1' : '0';
    }

    std::string result; auto node = root;
    for (char bit : compressedBits)
    {
        node = (bit == '0') ? node->left : node->right;
        if (node->isLeaf()) { result += node->data; node = root; }
    }

    return result;
}

std::string readFile(const std::string &filename)
{
    std::ifstream f(filename, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filename, const std::string &data)
{
    std::ofstream f(filename, std::ios::binary);
    f.write(data.data(), data.size());
}
