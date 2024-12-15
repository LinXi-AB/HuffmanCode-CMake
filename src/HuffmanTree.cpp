#include "HuffmanTree.h"

void HuffmanTree::deleteTree(HuffmanTreeNode* root)
{
	if (root != nullptr) // 如何使用智能指针
	{
		deleteTree(root->getLeftChild());
		deleteTree(root->getRightChild());
		delete root;
	}
}

void HuffmanTree::initHuffmanTree(FrequencyPriorityQueue frequency_priority_queue)
{
	if (frequency_priority_queue.size() == 1)
	{
		this->root = new HuffmanTreeNode('\0', frequency_priority_queue.top()->getFrequency());// 可以使用类工厂指出参数含义(让函数名体现出参数含义)
		this->root->setLeftChildTo(frequency_priority_queue.top());
		return;
	}

	while (frequency_priority_queue.size() > 1)
	{
		HuffmanTreeNode* left_child = frequency_priority_queue.top();
		frequency_priority_queue.pop();
		HuffmanTreeNode* right_child = frequency_priority_queue.top();
		frequency_priority_queue.pop();
		HuffmanTreeNode* new_root = new HuffmanTreeNode('\0', left_child->getFrequency() + right_child->getFrequency());
		new_root->setLeftChildTo(left_child);
		new_root->setRightChildTo(right_child);
		frequency_priority_queue.push(new_root);
	}
	root = frequency_priority_queue.top();
}

void HuffmanTree::generateCodeIn(std::unordered_map<char, std::string>& code_sheet) const
{
	if (root == nullptr)
		return;

	generateCodeStepIn(root->getLeftChild(), "0", code_sheet);
	generateCodeStepIn(root->getRightChild(), "1", code_sheet);
}

void HuffmanTree::generateCodeStepIn(const HuffmanTreeNode* root, std::string current_code, std::unordered_map<char, std::string>& code_sheet) const
{
	if (root == nullptr)
		return;

	if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr)
	{
		code_sheet[root->getCh()] = current_code;
	}

	generateCodeStepIn(root->getLeftChild(), current_code + "0", code_sheet);
	generateCodeStepIn(root->getRightChild(), current_code + "1", code_sheet);
}

// 此函数由gpt生成，不进行优化
void HuffmanTree::printTree(const HuffmanTreeNode* root, std::string prefix = "", bool isLeft = true) const
{
	if (root == nullptr)
	{
		return;
	}

	std::cout << prefix;
	std::cout << (isLeft ? "|-- " : "`-- ");

	if (root->getCh() != '\0')
	{
		std::cout << root->getCh() << " (" << root->getFrequency() << ")\n";
	}
	else
	{
		std::cout << "* (" << root->getFrequency() << ")\n";
	}

	printTree(root->getLeftChild(), prefix + (isLeft ? "|   " : "    "), true);
	printTree(root->getRightChild(), prefix + (isLeft ? "|   " : "    "), false);
}

HuffmanTreeNode* HuffmanTree::getRoot() const
{
	return root;
}
