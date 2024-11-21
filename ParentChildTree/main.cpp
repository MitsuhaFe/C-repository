#include <iostream>
#include <cstdlib>
#define MAX_TREE_SIZE 20
using namespace std;

//孩子节点结构
typedef struct CTNode {
    int child;
    struct CTNode  *next;
} *ChildPtr;

//双亲节点结构
typedef struct {
    char data;
    ChildPtr firstchild;
    // 孩子链表头指针
} CTBox;

//树结构
typedef struct {
    CTBox nodes[MAX_TREE_SIZE];
    int parent;//双亲的位置
    int n,r;   // 结点数和根结点的位置
} CTree;

// 创建孩子节点
ChildPtr CreateChild(int child) {
    ChildPtr newChild = (ChildPtr)malloc(sizeof(struct CTNode));
    if (newChild != NULL) {
        newChild->child = child;
        newChild->next = NULL;
    }
    return newChild;
}

// 初始化树
void InitTree(CTree *tree) {
    tree->n = 6; // 树的节点数
    tree->r = 0; // 根结点的位置
    tree->parent = -1; // 根结点没有双亲

    // 初始化所有节点的数据和孩子链表头指针
    for (int i = 0; i < tree->n; ++i) {
        tree->nodes[i].data = 'A' + i;
        tree->nodes[i].firstchild = NULL;
    }

    // 构建孩子链表
    tree->nodes[0].firstchild = CreateChild(1);
    tree->nodes[0].firstchild->next = CreateChild(2);

    tree->nodes[1].firstchild = CreateChild(3);

    tree->nodes[2].firstchild = CreateChild(4);
    tree->nodes[2].firstchild->next = CreateChild(5);
}

// 计算一个结点的度
int DegreeOfNode(CTBox *node) {
    int degree = 0;
    ChildPtr current = node->firstchild;
    while (current != NULL) {
        degree++;
        current = current->next;
    }
    return degree;
}

// 计算树的度
int DegreeOfTree(CTree *tree) {
    int maxDegree = 0;
    for (int i = 0; i < tree->n; ++i) {
        int degree = DegreeOfNode(&tree->nodes[i]);
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}

// 示例使用
int main() {
    CTree tree;
    InitTree(&tree); // 初始化树

    int treeDegree = DegreeOfTree(&tree);
    printf("The degree of the tree is: %d\n", treeDegree);

    // 释放分配的内存
    for (int i = 0; i < tree.n; ++i) {
        ChildPtr current = tree.nodes[i].firstchild;
        while (current != NULL) {
            ChildPtr temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}