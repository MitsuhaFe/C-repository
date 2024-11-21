#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data[10]; // 存储操作数或操作符
    struct node *left, *right;
} BTree;

// 函数声明
//void convertToInfix(BTree *root, char *result, int *index);

// 创建新节点
BTree* newNode(const char* value) {
    BTree* node = (BTree*)malloc(sizeof(BTree));
    strcpy(node->data, value);
    node->left = node->right = NULL;
    return node;
}

// 主函数，用于转换表达式树到中缀表达式
void convertToInfix(BTree *root, char *result, int *index) {
    if (root == NULL) {
        return;
    }

    // 如果是操作数，直接添加到结果字符串
    if (root->left == NULL && root->right == NULL) {
        sprintf(result + *index, "%s", root->data);
        *index += strlen(root->data);
        return;
    }

    // 添加左括号
    result[(*index)++] = '(';

    // 递归转换左子树
    convertToInfix(root->left, result, index);

    // 添加操作符
    sprintf(result + *index, "%s", root->data);
    *index += strlen(root->data);

    // 递归转换右子树
    convertToInfix(root->right, result, index);

    // 添加右括号
    result[(*index)++] = ')';
}

int main() {
    // 构建表达式树
    BTree *root1 = newNode("*");
    root1->left = newNode("+");
    root1->left->left=newNode("a");
    root1->left->right=newNode("b");
    root1->right = newNode("*");
    root1->right->left = newNode("c");
    root1->right->right = newNode("-");
    root1->right->right->right = newNode("d");

    BTree *root2 = newNode("+");
    root2->left = newNode("*");
    root2->left->left = newNode("a");
    root2->left->right = newNode("b");
    root2->right = newNode("-");
    root2->right->left = newNode("c");
    root2->right->right = newNode("d");

    // 转换并输出结果
    char result1[100];
    int index1 = 0;
    convertToInfix(root1, result1, &index1);
    result1[index1] = '\0'; // 添加字符串结束符
    printf("Infix Expression 1: %s\n", result1);

    char result2[100];
    int index2 = 0;
    convertToInfix(root2, result2, &index2);
    result2[index2] = '\0'; // 添加字符串结束符
    printf("Infix Expression 2: %s\n", result2);

    // 释放内存
    // 注意：这里没有释放所有节点的内存，实际使用时需要递归释放每个节点
    free(root1);
    free(root2);

    return 0;
}
