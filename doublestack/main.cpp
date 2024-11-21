#include <iostream>
using namespace std;

typedef struct {
    char base[100];
    int top1;
    int top2;
}doubleStack;

void initDoubleStack(doubleStack *S) {
    S->top1=0;
    S->top2=99;

}

int push(doubleStack* S,char ch,int stackNumber) {
    if(stackNumber==1) {
        S->base[S->top1]=ch;
        S->top1++;
        return 0;
    }if(stackNumber==2) {
        S->base[S->top2]=ch;
        S->top2--;
        return 0;
    }else
        return 1;
}

char pop(doubleStack* S,char* ch,int stackNumber) {
    if(stackNumber==1) {
        *ch=S->base[S->top1-1];
        S->top1--;
        return *ch;
    }if(stackNumber==2) {
        *ch=S->base[S->top2+1];
        S->top2++;
        return *ch;
    }
}

void output(doubleStack* S) {
    cout<<"doubleStack1:";
    for(int i = S->top1-1;i >= 0;i--) {
        cout<<S->base[i];
    }
    cout<<endl<<"doubleStack2:";
    for(int j = S->top2+1;j <= 99;j++)
    {
        cout<<S->base[j];
    }
    cout<<endl;
}
int main() {
    doubleStack newStack;
    doubleStack* pointStack = &newStack;
    char newchar;
    char* ch=&newchar;
    initDoubleStack(pointStack);

    push(pointStack,'a',1);
    push(pointStack,'b',2);
    push(pointStack,'c',1);
    push(pointStack,'d',2);
    push(pointStack,'e',1);
    push(pointStack,'f',2);
    output(pointStack);

    pop(pointStack,ch,1);
    cout<<"pop char:"<<*ch<<endl;
    output(pointStack);

    pop(pointStack,ch,2);
    cout<<"pop char:"<<*ch<<endl;
    output(pointStack);

    return 0;
}
