// ��ʵ�֣�ʹ�ù�����������

#include "FrequencyCompare.h"
#include "HuffmanTree.h"
#include "HuffmanTreeNode.h"
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

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

std::unordered_map<char, int> HuffmanCodec::calculateCharFrequency(const std::string& raw_text)
{
	std::unordered_map<char, int> frequency_map;
	for (const auto& ch : raw_text) {
		frequency_map[ch]++;
	}
	return frequency_map;
}

FrequencyPriorityQueue HuffmanCodec::buildPriorityQueueFrom(const std::unordered_map<char, int>& frequency_map)
{
	std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, FrequencyCompare> priority_queue;
	for (const auto& [ch, frequency] : frequency_map) {
		priority_queue.push(new HuffmanTreeNode(ch, frequency));
	}
	return priority_queue;
}

HuffmanTree HuffmanCodec::buildHuffmanTreeFrom(const FrequencyPriorityQueue& priority_queue)
{
	HuffmanTree huffman_tree;
	huffman_tree.initHuffmanTree(priority_queue);

	/* ���� */
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
	for (const auto& ch : raw_text) {
		encoded_str += char_to_code_map.at(ch);
	}
	return encoded_str;
}

std::unordered_map<std::string, char> HuffmanCodec::createCodeToCharMap(const std::unordered_map<char, std::string>& char_to_code_map)
{
	std::unordered_map<std::string, char> code_to_ch_map;
	for (const auto& [ch, code] : char_to_code_map) {
		code_to_ch_map[code] = ch;
	}
	return code_to_ch_map;
}

std::string HuffmanCodec::decodeText(const std::string& encoded_text, const std::unordered_map<std::string, char>& code_to_ch_map)
{
	std::string decoded_str;
	std::string accumulated_compare_code;
	for (const auto& ch : encoded_text) {
		accumulated_compare_code += ch;
		const auto& it = code_to_ch_map.find(accumulated_compare_code);
		if (it != code_to_ch_map.end()) {
			decoded_str += it->second;
			accumulated_compare_code.clear();
		}
	}
	return decoded_str;
}

std::pair<std::string, std::unordered_map<char, std::string>> HuffmanCodec::encode(const std::string& raw_text)
{
	// �ַ���Ϊ���򷵻ؿ�pair
	if (raw_text.empty())
		return { "", {} };

	// Step 1: ͳ���ַ�Ƶ��
	auto char_frequency_map = calculateCharFrequency(raw_text);

	// Step 2: �����ַ�Ƶ�ʹ������ȶ���
	auto frequency_priority_queue = buildPriorityQueueFrom(char_frequency_map);

	// Step 3: �������ȶ���(�ַ�Ƶ��)������������
	HuffmanTree huffman_tree = buildHuffmanTreeFrom(frequency_priority_queue);

	// Step 4: �ӹ����������ɱ����
	auto char_to_code_map = generateCharToCodeMapFrom(huffman_tree);

	// Step 5: ʹ�ñ�������ԭ�ı�
	std::string encoded_str = encodeText(raw_text, char_to_code_map);

	return { encoded_str, char_to_code_map };
}

std::string HuffmanCodec::decode(const std::string& encoded_text, const std::unordered_map<char, std::string>& char_to_code_map)
{
	// Step 1: ��������ӳ���
	auto code_to_ch_map = createCodeToCharMap(char_to_code_map);

	// Step 2: ʹ�ý��������ı�
	return decodeText(encoded_text, code_to_ch_map);
}

int main()
{
	std::string input_text;
	std::cout << "����������Ҫѹ�����ַ���:";
	std::getline(std::cin, input_text);

	HuffmanCodec huffman_codec;
	auto [encoded_text, ch_to_code_map] = huffman_codec.encode(input_text);
	std::cout << "�������ı���: " << encoded_text << std::endl;

	std::string decoded_text;
	decoded_text = huffman_codec.decode(encoded_text, ch_to_code_map);
	std::cout << "�������ı���: " << decoded_text << std::endl;

	return 0;
}
