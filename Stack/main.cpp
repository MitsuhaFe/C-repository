#include <iostream>
using namespace std;

typedef struct{
    char base[50];
    int top;
}Stack;

int push(Stack *S,char ch) {
    if(S->top==0) {
        return 0;
    }else {
        S->top--;
        S->base[S->top]=ch;
        cout<<S->base[S->top]<<endl;
        return 1;
    }
}

int pop(Stack* S) {
    if(S->top==50) {
        return 0;
    }else {
        S->top++;
    }
    cout<<S->base[S->top]<<endl;
    return 1;
}

int StackLength(Stack* S) {
    return 50-S->top;
}

int main() {

    Stack newStack;
    Stack* point =&newStack;
    newStack.top=50;

    char ch1 = 'a';
    char ch2 = 'b';
    char ch3 = 'c';

    push(point,ch1);
    cout<<StackLength(point)<<endl;
    push(point,ch2);
    cout<<StackLength(point)<<endl;
    push(point,ch3);
    cout<<StackLength(point)<<endl;

    pop(point);
    cout<<StackLength(point)<<endl;

    return 0;
}
