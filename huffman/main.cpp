#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <bitset>
#include <sstream>

// ���������ڵ�ṹ
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
        // ͳ��Ƶ��
        std::map<char, unsigned> frequencies;
        for (char c : input) {
            frequencies[c]++;
        }

        // ������������
        buildHuffmanTree(frequencies);

        // ��ʾ�����
        std::cout << "\n�����" << std::endl;
        for (const auto& pair : huffmanCodes) {
            std::cout << "�ַ� '" << pair.first << "' : " << pair.second << std::endl;
        }

        // ѹ������
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

    // ��ʾѹ����
    void showCompressionRate(const std::string& original, const std::string& compressed) {
        double originalBits = original.length() * 8;  // ԭʼ�ַ�����λ��
        double compressedBits = compressed.length();  // ѹ�����λ��
        double rate = (originalBits - compressedBits) / originalBits * 100;

        std::cout << "\nѹ��ͳ�ƣ�" << std::endl;
        std::cout << "ԭʼ��С��" << originalBits << " λ" << std::endl;
        std::cout << "ѹ�����С��" << compressedBits << " λ" << std::endl;
        std::cout << "ѹ���ʣ�" << rate << "%" << std::endl;
    }
};

int main() {
    HuffmanCompression huffman;
    std::string input;

    std::cout << "������Ҫѹ�����ַ�����";
    std::getline(std::cin, input);

    std::cout << "\nԭʼ�ַ�����" << input << std::endl;

    // ѹ��
    std::string compressed = huffman.compress(input);
    std::cout << "\nѹ����Ķ����ƴ���" << compressed << std::endl;

    // ��ѹ
    std::string decompressed = huffman.decompress(compressed);
    std::cout << "\n��ѹ����ַ�����" << decompressed << std::endl;

    // ��ʾѹ����
    huffman.showCompressionRate(input, compressed);

    system("pause");
    return 0;
}