#include "huffman.h"
#include <fstream>
#include <bitset>

HuffmanCompression::~HuffmanCompression() {
    cleanup(root);
}

void HuffmanCompression::cleanup(HuffmanNode* node) {
    if (node) {
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }
}

void HuffmanCompression::buildHuffmanTree(const map<char, unsigned>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pq;
    
    // 创建叶子节点并加入优先队列
    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // 构建哈夫曼树
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    root = pq.top();
    
    // 生成编码表
    huffmanCodes.clear();
    generateCodes(root, "");
}

void HuffmanCompression::generateCodes(HuffmanNode* node, string code) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        huffmanCodes[node->data] = code;
    }
    
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanCompression::compress(const string& inputFile, const string& outputFile) {
    // 读取输入文件并统计频率
    map<char, unsigned> frequencies;
    ifstream inFile(inputFile, ios::binary);
    char ch;
    while (inFile.get(ch)) {
        frequencies[ch]++;
    }
    inFile.close();
    
    // 构建哈夫曼树
    buildHuffmanTree(frequencies);
    
    // 压缩文件
    inFile.open(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    // 写入字符频率表
    outFile << frequencies.size() << '\n';
    for (const auto& pair : frequencies) {
        outFile << pair.first << ' ' << pair.second << '\n';
    }
    
    // 压缩数据
    string bits;
    while (inFile.get(ch)) {
        bits += huffmanCodes[ch];
    }
    
    // 写入压缩后的数据
    while (bits.length() % 8 != 0) {
        bits += "0";  // 补齐到字节
    }
    
    for (size_t i = 0; i < bits.length(); i += 8) {
        char byte = bitset<8>(bits.substr(i, 8)).to_ulong();
        outFile.put(byte);
    }
    
    inFile.close();
    outFile.close();
}

void HuffmanCompression::decompress(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile);
    
    // 读取频率表并重建哈夫曼树
    map<char, unsigned> frequencies;
    size_t tableSize;
    inFile >> tableSize;
    inFile.get(); // 读取换行符
    
    for (size_t i = 0; i < tableSize; i++) {
        char ch;
        unsigned freq;
        ch = inFile.get();
        inFile.get(); // 读取空格
        inFile >> freq;
        inFile.get(); // 读取换行符
        frequencies[ch] = freq;
    }
    
    buildHuffmanTree(frequencies);
    
    // 解压数据
    HuffmanNode* current = root;
    char byte;
    while (inFile.get(byte)) {
        bitset<8> bits(byte);
        for (int i = 7; i >= 0; i--) {
            if (bits[i] == 0) {
                current = current->left;
            } else {
                current = current->right;
            }
            
            if (!current->left && !current->right) {
                outFile.put(current->data);
                current = root;
            }
        }
    }
    
    inFile.close();
    outFile.close();
} 