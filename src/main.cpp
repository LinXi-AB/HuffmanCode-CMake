// ��ʵ�֣�ʹ�ù�����������

#include "FrequencyCompare.h"
#include "HuffmanCodec.h"
#include "HuffmanTreeNode.h"
#include <iostream>

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

	getchar();
	return 0;
}
