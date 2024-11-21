#ifndef HUFFMAN_H
#define HUFFMAN_H
using namespace std;

#include <string>
#include <map>
#include <queue>
#include <vector>

// 哈夫曼树节点结构
struct HuffmanNode {
    char data;              // 字符
    unsigned frequency;     // 频率
    HuffmanNode* left;     // 左子节点
    HuffmanNode* right;    // 右子节点
    
    HuffmanNode(char d, unsigned freq) : 
        data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

// 用于优先队列比较的结构
struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCompression {
private:
    HuffmanNode* root;
    map<char, string> huffmanCodes;
    
    void generateCodes(HuffmanNode* root, string code);
    void cleanup(HuffmanNode* node);
    
public:
    HuffmanCompression() : root(nullptr) {}
    ~HuffmanCompression();
    
    void buildHuffmanTree(const map<char, unsigned>& frequencies);
    void compress(const string& inputFile, const string& outputFile);
    void decompress(const string& inputFile, const string& outputFile);
};

#endif 