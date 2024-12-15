#pragma once

class HuffmanTreeNode
{
private:
    char ch;
    int frequency;
    HuffmanTreeNode* left_child;
    HuffmanTreeNode* right_child;

public:
    explicit HuffmanTreeNode(char ch, int freq);
    ~HuffmanTreeNode();

    int getFrequency() const;
    HuffmanTreeNode* getLeftChild() const;
    HuffmanTreeNode* getRightChild() const;
    char getCh() const;
    void setLeftChildTo(HuffmanTreeNode* node);
    void setRightChildTo(HuffmanTreeNode* node);
};