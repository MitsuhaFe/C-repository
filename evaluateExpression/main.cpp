#include <iostream>
using namespace std;

typedef struct{
    char base[50];
    int top;
}Stack;

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: return 0;
    }
}

int push(Stack *S,char ch) {
    if(S->top==50) {
        return 0;
    }else {
        S->top++;
        S->base[S->top]=ch;
        //cout<<S->base[S->top]<<endl;
        return 1;
    }
}

char pop(Stack* S,char* exprr) {
    if(S->top==0) {
        return 0;
    }else {
        *exprr==S->top;
        S->top--;
    }
    //cout<<S->base[S->top]<<endl;
    return 1;
}

char top(Stack *S) {
    return S->base[S->top];
}

int evaluate(char* ch) {
    char expr;
    char *exprr=&expr;
    int i=0,x=0;
    Stack op,num;
    Stack *opp=&op;
    Stack *nump=&num;
    op.top=0;
    num.top=0;
    while(ch[i]!=',') {
        if(i==0||('0'<=ch[i]&&ch[i]<='9')) {
            cout<<ch[i];
            if(x==0) {
                push(nump,ch[i]);
            }else {
                int a=top(nump);
                int b=ch[i];
                cout<<endl;
                cout<<"a:"<<a<<"    "<<"nump:"<<top(nump)<<endl;
                cout<<"b:"<<b<<"    "<<"ch[i]:"<<ch[i]<<endl;
                //cout<<calculate(a,b,expr);
            }

            //cout<<ch[i];
        }
        if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/') {
            //cout<<ch[i];
            //cout<<top(opp);
            if((top(opp)=='*'||top(opp)=='/')&&(ch[i]=='+'||ch[i]=='-')) {
                pop(opp,exprr);
                x++;
                //cout<<"x:"<<x<<endl;
            }
            else {
                push(opp,ch[i]);
                //cout<<ch[i];
            }
            //cout<<ch[i];
        }
        i++;
    }

}

int main() {
    char ch[100];
    int num=0;
    while((cin>>ch[num])&&ch[num]!=',') {
        num++;
    }
    evaluate(ch);
    return 0;
}
