#include <iostream>
using namespace std;

typedef struct QNode{
    char data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
    QueuePtr front,rear;
}LinkQueue;

void EnQueue(LinkQueue* Q,char ch) {
    QueuePtr s =(QueuePtr)malloc (sizeof(QNode));
    s->data=ch;
    s->next=NULL;
    Q->rear->next=s;
    Q->rear=s;

}
char DeQueue(LinkQueue* Q,char* ch) {
    QueuePtr p;
    if(Q->front==Q->rear)
        return 0;
    p=Q->front->next;
    *ch=p->data;
    Q->front->next=p->next;
    if(Q->rear==p)
        Q->rear=Q->front;
    free(p);
    return *ch;
}
void output(LinkQueue*Q) {
    
}

int main() {

    return 0;
}
