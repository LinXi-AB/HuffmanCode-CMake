// 待实现：使用哈夫曼树解码

#include "FrequencyCompare.h"
#include "HuffmanCodec.h"
#include "HuffmanTreeNode.h"
#include <iostream>

int main()
{
	std::string input_text;
	std::cout << "请输入您需要压缩的字符串:";
	std::getline(std::cin, input_text);

	HuffmanCodec huffman_codec;
	auto [encoded_text, ch_to_code_map] = huffman_codec.encode(input_text);
	std::cout << "编码后的文本是: " << encoded_text << std::endl;

	std::string decoded_text;
	decoded_text = huffman_codec.decode(encoded_text, ch_to_code_map);
	std::cout << "解码后的文本是: " << decoded_text << std::endl;

	getchar();
	return 0;
}
