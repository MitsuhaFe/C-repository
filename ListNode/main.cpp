#include <iostream>
#include <cstdlib>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* Init() {
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    if (head == NULL) {
        exit(-1);
    }
    head->value = 0;
    head->next = NULL;
    return head;
}

void Append(ListNode *head, int value) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        exit(-1);
    }
    newNode->value = value;
    newNode->next = NULL;

    ListNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void InsertList(ListNode *head, int position, int value) {
    if (position < 0) {
        printf("输入不合法\n");
        return;
    }

    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        exit(-1);
    }
    newNode->value = value;

    ListNode *current = head;
    int index = 0;

    while (current != NULL && index < position) {
        if (current->next == NULL && index == position - 1) {
            break;
        }
        current = current->next;
        index++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Int Getelem() {
//
// }

void DeleteList(ListNode *head,int position) {
    ListNode *current = head->next;
    ListNode *newNode = head;
    int index =0;

    while (current !=NULL && index < position) {
        if (current->next == NULL && index == position - 1) {
            break;
        }
        current = current->next;
        newNode = newNode->next;
        index++;
    }

    newNode->next =current->next;
}

void PrintList(ListNode *head) {
    ListNode *current = head->next;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    ListNode *list = Init();

    for (int i = 1; i <= 5; ++i) {
        Append(list, i);
    }

    PrintList(list);

    InsertList(list,2,5);
    PrintList(list);

    DeleteList(list,3);
    PrintList(list);

    return 0;
}



int judge(DNode *head) {
    if (head == NULL || head->next == head) {
        return 1;
    }

    DNode *p = head->next;
    DNode *q = head->prev;

    while (p != q && p->next != q) {
        if (p->data != q->data) {
            return 0;
        }
        p = p->next;
        q = q->prev;
    }

    return 1;
}

void deleteX(LNode *head, int x) {
    LNode *p = head->next;
    LNode *q = NULL;

    while (p != NULL) {
        if (p->data == x) {
            q->next = p->next;
            free(p);
            p = q->next;
        } else {
            q = p;
            p = p->next;
        }
    }
}