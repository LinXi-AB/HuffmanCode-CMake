#include "HuffmanCodec.h"
#include <gtest/gtest.h>

// 测试空字符串
TEST(HuffmanCodecTest, EmptyString)
{
	HuffmanCodec codec;
	auto [encoded_text, char_to_code_map] = codec.encode("");
	EXPECT_EQ(encoded_text, "");
	EXPECT_EQ(codec.decode("", char_to_code_map), "");
}

// 测试单字符字符串
TEST(HuffmanCodecTest, SingleCharacter)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("a"); 
    EXPECT_EQ(encoded_text, "0"); 
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "a");
}

// 测试重复字符字符串
TEST(HuffmanCodecTest, RepeatedCharacters)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("aaaaa");
    EXPECT_EQ(encoded_text, "00000");
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "aaaaa");
}

// 测试包含空格和特殊字符的一般字符串
TEST(HuffmanCodecTest, SpecialCharacters)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("你好 world! □"); // 包含空格和特殊字符
    EXPECT_NE(encoded_text, "你好 world! □"); // 编码后的文本应该与原始文本不同
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "你好 world! □"); // 解码后应该是 "hello world!"
}