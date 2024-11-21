#include "huffman.h"
#include <iostream>

int main() {
    HuffmanCompression huffman;
    
    // 测试压缩
    cout << "正在压缩文件..." << endl;
    huffman.compress("input.txt", "compressed.bin");
    
    // 测试解压
    cout << "正在解压文件..." << endl;
    huffman.decompress("compressed.bin", "decompressed.txt");
    
    cout << "完成！" << endl;
    return 0;
} 