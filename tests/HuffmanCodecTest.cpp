#include "HuffmanCodec.h"
#include <gtest/gtest.h>

/// @test ���Կ��ַ���
TEST(HuffmanCodecTest, EmptyString)
{
	HuffmanCodec codec;
	auto [encoded_text, char_to_code_map] = codec.encode("");
	EXPECT_EQ(encoded_text, "");
	EXPECT_EQ(codec.decode("", char_to_code_map), "");
}

/// @test ���Ե��ַ��ַ���
TEST(HuffmanCodecTest, SingleCharacter)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("a"); 
    EXPECT_EQ(encoded_text, "0"); 
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "a");
}

/// @test �����ظ��ַ��ַ���
TEST(HuffmanCodecTest, RepeatedCharacters)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("aaaaa");
    EXPECT_EQ(encoded_text, "00000");
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "aaaaa");
}

/// @test ���԰����ո�������ַ���һ���ַ���
TEST(HuffmanCodecTest, SpecialCharacters)
{
    HuffmanCodec codec;
    auto [encoded_text, char_to_code_map] = codec.encode("��� world! ��"); // �����ո�������ַ�
    EXPECT_NE(encoded_text, "��� world! ��"); // �������ı�Ӧ����ԭʼ�ı���ͬ
    EXPECT_EQ(codec.decode(encoded_text, char_to_code_map), "��� world! ��"); // �����Ӧ���� "hello world!"
}