#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <bitset>
#include <sstream>

// 哈夫曼树节点结构
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char d, unsigned freq) :
        data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCompression {
private:
    HuffmanNode* root;
    std::map<char, std::string> huffmanCodes;

    void generateCodes(HuffmanNode* node, std::string code) {
        if (node) {
            if (!node->left && !node->right) {
                huffmanCodes[node->data] = code;
            }
            generateCodes(node->left, code + "0");
            generateCodes(node->right, code + "1");
        }
    }

    void cleanup(HuffmanNode* node) {
        if (node) {
            cleanup(node->left);
            cleanup(node->right);
            delete node;
        }
    }

public:
    HuffmanCompression() : root(nullptr) {}

    ~HuffmanCompression() {
        cleanup(root);
    }

    void buildHuffmanTree(const std::map<char, unsigned>& frequencies) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> pq;

        for (const auto& pair : frequencies) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();

            HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();
        huffmanCodes.clear();
        generateCodes(root, "");
    }

    std::string compress(const std::string& input) {
        // 统计频率
        std::map<char, unsigned> frequencies;
        for (char c : input) {
            frequencies[c]++;
        }

        // 构建哈夫曼树
        buildHuffmanTree(frequencies);

        // 显示编码表
        std::cout << "\n编码表：" << std::endl;
        for (const auto& pair : huffmanCodes) {
            std::cout << "字符 '" << pair.first << "' : " << pair.second << std::endl;
        }

        // 压缩数据
        std::string compressed;
        for (char c : input) {
            compressed += huffmanCodes[c];
        }

        return compressed;
    }

    std::string decompress(const std::string& bits) {
        std::string result;
        HuffmanNode* current = root;

        for (char bit : bits) {
            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }

            if (!current->left && !current->right) {
                result += current->data;
                current = root;
            }
        }

        return result;
    }

    // 显示压缩率
    void showCompressionRate(const std::string& original, const std::string& compressed) {
        double originalBits = original.length() * 8;  // 原始字符串的位数
        double compressedBits = compressed.length();  // 压缩后的位数
        double rate = (originalBits - compressedBits) / originalBits * 100;

        std::cout << "\n压缩统计：" << std::endl;
        std::cout << "原始大小：" << originalBits << " 位" << std::endl;
        std::cout << "压缩后大小：" << compressedBits << " 位" << std::endl;
        std::cout << "压缩率：" << rate << "%" << std::endl;
    }
};

int main() {
    HuffmanCompression huffman;
    std::string input;

    std::cout << "请输入要压缩的字符串：";
    std::getline(std::cin, input);

    std::cout << "\n原始字符串：" << input << std::endl;

    // 压缩
    std::string compressed = huffman.compress(input);
    std::cout << "\n压缩后的二进制串：" << compressed << std::endl;

    // 解压
    std::string decompressed = huffman.decompress(compressed);
    std::cout << "\n解压后的字符串：" << decompressed << std::endl;

    // 显示压缩率
    huffman.showCompressionRate(input, compressed);

    system("pause");
    return 0;
}