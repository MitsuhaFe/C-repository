#include "huffman.h"
#include <iostream>

int main() {
    HuffmanCompression huffman;
    
    // ����ѹ��
    cout << "����ѹ���ļ�..." << endl;
    huffman.compress("input.txt", "compressed.bin");
    
    // ���Խ�ѹ
    cout << "���ڽ�ѹ�ļ�..." << endl;
    huffman.decompress("compressed.bin", "decompressed.txt");
    
    cout << "��ɣ�" << endl;
    return 0;
} 