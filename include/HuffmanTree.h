#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include <iostream>
#include "HuffmanTreeNode.h"
#include "FrequencyCompare.h"

using FrequencyPriorityQueue = std::priority_queue<HuffmanTreeNode*,
	std::vector<HuffmanTreeNode*>, FrequencyCompare>;

class HuffmanTree
{
private:
	HuffmanTreeNode* root;

public:
	HuffmanTree() = default;
	~HuffmanTree() = default;

	void deleteTree(HuffmanTreeNode* root);
	void initHuffmanTree(FrequencyPriorityQueue huffman_queue);// 按值传递防止一次性代码
	void generateCodeIn(std::unordered_map<char, std::string>& code_sheet) const;
	void generateCodeStepIn(const HuffmanTreeNode* root, std::string current_code, std::unordered_map<char, std::string>& code_sheet) const;
	void printTree(const HuffmanTreeNode* root, std::string prefix, bool isLeft) const;

	HuffmanTreeNode* getRoot() const;
};