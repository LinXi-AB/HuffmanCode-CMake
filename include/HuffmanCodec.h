#pragma once
#include <queue>
#include <unordered_map>
#include <string>
#include "HuffmanTree.h"

using FrequencyPriorityQueue = std::priority_queue<HuffmanTreeNode*,
	std::vector<HuffmanTreeNode*>, FrequencyCompare>;

class HuffmanCodec
{
public:
	HuffmanCodec() = default;
	std::pair<std::string, std::unordered_map<char, std::string>> encode(const std::string& raw_text);
	std::string decode(const std::string& encoded_text, const std::unordered_map<char, std::string>& ch_to_code_map);

private:
	std::unordered_map<char, int> calculateCharFrequency(const std::string& raw_text);
	FrequencyPriorityQueue buildPriorityQueueFrom(const std::unordered_map<char, int>& frequency_map);
	HuffmanTree buildHuffmanTreeFrom(const FrequencyPriorityQueue& priority_queue);
	std::unordered_map<char, std::string> generateCharToCodeMapFrom(const HuffmanTree& tree);
	std::string encodeText(const std::string& raw_text, const std::unordered_map<char, std::string>& char_to_code_map);
	std::unordered_map<std::string, char> createCodeToCharMap(const std::unordered_map<char, std::string>& char_to_code_map);
	std::string decodeText(const std::string& encoded_text, const std::unordered_map<std::string, char>& code_to_ch_map);
};
