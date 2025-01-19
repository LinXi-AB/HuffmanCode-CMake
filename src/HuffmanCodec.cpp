#include "HuffmanCodec.h"

using FrequencyPriorityQueue = std::priority_queue<HuffmanTreeNode*,
	std::vector<HuffmanTreeNode*>, FrequencyCompare>;

std::unordered_map<char, int> HuffmanCodec::calculateCharFrequency(const std::string& raw_text)
{
	std::unordered_map<char, int> frequency_map;
	for (const auto& ch : raw_text)
	{
		frequency_map[ch]++;
	}
	return frequency_map;
}

FrequencyPriorityQueue HuffmanCodec::buildPriorityQueueFrom(const std::unordered_map<char, int>& frequency_map)
{
	std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, FrequencyCompare> priority_queue;
	for (const auto& [ch, frequency] : frequency_map)
	{
		priority_queue.push(new HuffmanTreeNode(ch, frequency));
	}
	return priority_queue;
}

HuffmanTree HuffmanCodec::buildHuffmanTreeFrom(const FrequencyPriorityQueue& priority_queue)
{
	HuffmanTree huffman_tree;
	huffman_tree.initHuffmanTree(priority_queue);

	/* 调试 */
	huffman_tree.printTree(huffman_tree.getRoot(), "", true);

	return huffman_tree;
}

std::unordered_map<char, std::string> HuffmanCodec::generateCharToCodeMapFrom(const HuffmanTree& tree)
{
	std::unordered_map<char, std::string> char_to_code_map;
	tree.generateCodeIn(char_to_code_map);
	return char_to_code_map;
}

std::string HuffmanCodec::encodeText(const std::string& raw_text, const std::unordered_map<char, std::string>& char_to_code_map)
{
	std::string encoded_str;
	for (const auto& ch : raw_text)
	{
		encoded_str += char_to_code_map.at(ch);
	}
	return encoded_str;
}

/**
 * @brief 将字符映射哈希表的key和value反向
 * @param char_to_code_map 字符映射表
 * @return key和value对调后的字符映射表
 */
std::unordered_map<std::string, char> HuffmanCodec::createCodeToCharMap(const std::unordered_map<char, std::string>& char_to_code_map)
{
	std::unordered_map<std::string, char> code_to_ch_map;
	for (const auto& [ch, code] : char_to_code_map)
	{
		code_to_ch_map[code] = ch;
	}
	return code_to_ch_map;
}

/**
 * @brief 根据字符映射表解码字符串，类内部使用
 * @param encoded_text 编码后的字符串
 * @param code_to_ch_map 字符映射表
 * @return 解码后的字符串
 */
std::string HuffmanCodec::decodeText(const std::string& encoded_text, const std::unordered_map<std::string, char>& code_to_ch_map)
{
	std::string decoded_str;
	std::string accumulated_compare_code;
	for (const auto& ch : encoded_text)
	{
		accumulated_compare_code += ch;
		const auto& it = code_to_ch_map.find(accumulated_compare_code);
		if (it != code_to_ch_map.end())
		{
			decoded_str += it->second;
			accumulated_compare_code.clear();
		}
	}
	return decoded_str;
}

/**
 * @brief 将字符串编码压缩，该函数返回编码压缩后的字符串和字符映射表，供用户使用
 * @param raw_text 将要被编码压缩的原始字符串
 * @return 编码压缩后的字符串和字符映射表
 */
std::pair<std::string, std::unordered_map<char, std::string>> HuffmanCodec::encode(const std::string& raw_text)
{
	// 字符串为空则返回空pair
	if (raw_text.empty())
		return { "", {} };

	// Step 1: 统计字符频率
	auto char_frequency_map = calculateCharFrequency(raw_text);

	// Step 2: 根据字符频率构建优先队列
	auto frequency_priority_queue = buildPriorityQueueFrom(char_frequency_map);

	// Step 3: 根据优先队列(字符频率)构建哈夫曼树
	HuffmanTree huffman_tree = buildHuffmanTreeFrom(frequency_priority_queue);

	// Step 4: 从哈夫曼树生成编码表
	auto char_to_code_map = generateCharToCodeMapFrom(huffman_tree);

	// Step 5: 使用编码表编码原文本
	std::string encoded_str = encodeText(raw_text, char_to_code_map);

	return { encoded_str, char_to_code_map };
}

/**
 * @brief 将编码压缩后的字符串解压，供用户使用
 * @param encoded_text 被编码压缩后的字符串
 * @param char_to_code_map 字符映射表
 * @return 解压后的字符串
 */
std::string HuffmanCodec::decode(const std::string& encoded_text, const std::unordered_map<char, std::string>& char_to_code_map)
{
	// Step 1: 构建解码映射表
	auto code_to_ch_map = createCodeToCharMap(char_to_code_map);

	// Step 2: 使用解码表解码文本
	return decodeText(encoded_text, code_to_ch_map);
}