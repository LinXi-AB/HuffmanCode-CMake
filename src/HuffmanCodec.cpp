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
	for (const auto& ch : raw_text)
	{
		encoded_str += char_to_code_map.at(ch);
	}
	return encoded_str;
}

/**
 * @brief ���ַ�ӳ���ϣ���key��value����
 * @param char_to_code_map �ַ�ӳ���
 * @return key��value�Ե�����ַ�ӳ���
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
 * @brief �����ַ�ӳ�������ַ��������ڲ�ʹ��
 * @param encoded_text �������ַ���
 * @param code_to_ch_map �ַ�ӳ���
 * @return �������ַ���
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
 * @brief ���ַ�������ѹ�����ú������ر���ѹ������ַ������ַ�ӳ������û�ʹ��
 * @param raw_text ��Ҫ������ѹ����ԭʼ�ַ���
 * @return ����ѹ������ַ������ַ�ӳ���
 */
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

/**
 * @brief ������ѹ������ַ�����ѹ�����û�ʹ��
 * @param encoded_text ������ѹ������ַ���
 * @param char_to_code_map �ַ�ӳ���
 * @return ��ѹ����ַ���
 */
std::string HuffmanCodec::decode(const std::string& encoded_text, const std::unordered_map<char, std::string>& char_to_code_map)
{
	// Step 1: ��������ӳ���
	auto code_to_ch_map = createCodeToCharMap(char_to_code_map);

	// Step 2: ʹ�ý��������ı�
	return decodeText(encoded_text, code_to_ch_map);
}