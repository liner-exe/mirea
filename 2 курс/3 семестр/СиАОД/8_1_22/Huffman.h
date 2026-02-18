#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>
#include <queue>
#include <string>
#include <memory>
#include <cstring>

class HuffmanNode
{
public:
	int frequency;
	std::string data;
	std::shared_ptr<HuffmanNode> left;
	std::shared_ptr<HuffmanNode> right;

	HuffmanNode(std::string d, int f);
	bool isLeaf() const;
};

struct CompareNode
{
	bool operator()(const std::shared_ptr<HuffmanNode> &a,
					const std::shared_ptr<HuffmanNode> &b) const;
};

class HuffmanCoder
{
	std::shared_ptr<HuffmanNode> root;
	std::map<std::string, std::string> huffmanCodes;
	std::map<std::string, int> frequency;

	void countFrequencies(const std::string &text);
	void buildHuffmanTree();
	void generateCodes(std::shared_ptr<HuffmanNode> node, const std::string &code);
	std::string serializeTree(std::shared_ptr<HuffmanNode> node);
	std::shared_ptr<HuffmanNode> deserializeTree(const std::string &serialized, size_t &pos);

public:
	std::string compress(const std::string &text);
	std::string decompress(const std::string &compressedData);
};

std::string readFile(const std::string &filename);
void writeFile(const std::string &filename, const std::string &data);

#endif // HUFFMAN_H