#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_LEN 256


int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: return 0;
    }
}


int evaluateExpression(const char *expr) {
    int stack[MAX_EXPR_LEN];
    int top = -1;
    char operators[MAX_EXPR_LEN];
    int opTop = -1;

    for (int i = 0; expr[i] != '\0'; ++i) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;
            stack[++top] = num;
        } else {
            while (opTop != -1 && ((expr[i] == '+' || expr[i] == '-') ||
            (operators[opTop] == '*' || operators[opTop] == '/'))) {
                int b = stack[top--];
                int a = stack[top--];
                char op = operators[opTop--];
                stack[++top] = calculate(a, b, op);
            }
            operators[++opTop] = expr[i];
        }
    }


    while (opTop != -1) {
        int b = stack[top--];
        int a = stack[top--];
        char op = operators[opTop--];
        stack[++top] = calculate(a, b, op);
    }

    return stack[top];
}

int main() {
    char expr[MAX_EXPR_LEN];
    printf("Enter an expression: ");
    fgets(expr, MAX_EXPR_LEN, stdin);
    expr[strcspn(expr, "\n")] = 0;

    int result = evaluateExpression(expr);
    printf("The result is: %d\n", result);
    return 0;
}