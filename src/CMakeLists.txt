# 将Huffman编码模块打包为lib
set(HuffmanCode_LIB_FILES
    FrequencyCompare.cpp
    HuffmanCodec.cpp
    HuffmanTree.cpp
    HuffmanTreeNode.cpp
)
add_library(HuffmanCodeLib STATIC ${HuffmanCode_LIB_FILES})

add_executable(HuffmanCode main.cpp)
target_link_libraries(HuffmanCode HuffmanCodeLib)