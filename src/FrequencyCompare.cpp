#include "FrequencyCompare.h"

bool FrequencyCompare::operator()(HuffmanTreeNode* node1, HuffmanTreeNode* node2) 
{
    return node1->getFrequency() > node2->getFrequency();
}
