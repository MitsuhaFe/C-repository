#include <stdio.h>
#include <stdlib.h>

// 定义多项式的项结构体
typedef struct PolyItem {
    int coef; // 系数
    int exp;  // 指数
    struct PolyItem *next;
} PolyItem;

// 创建一个新的多项式项
PolyItem* createItem(int coef, int exp) {
    PolyItem *item = (PolyItem*)malloc(sizeof(PolyItem));
    if (item != NULL) {
        item->coef = coef;
        item->exp = exp;
        item->next = NULL;
    }
    return item;
}

// 将新项添加到多项式的末尾
void appendItem(PolyItem **poly, PolyItem *item) {
    if (*poly == NULL) {
        *poly = item;
    } else {
        PolyItem *current = *poly;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = item;
    }
}

// 加载多项式
void loadPoly(PolyItem **poly) {
    int coef, exp;
    printf("Enter the coefficients and exponents of the polynomial (enter -1 -1 to end):\n");
    while (1) {
        scanf("%d %d", &coef, &exp);
        if (coef == -1 && exp == -1) {
            break;
        }
        PolyItem *item = createItem(coef, exp);
        appendItem(poly, item);
    }
}

// 多项式相加
PolyItem* addPolynomials(PolyItem *poly1, PolyItem *poly2) {
    PolyItem *result = NULL;
    PolyItem *current1 = poly1, *current2 = poly2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exp > current2->exp) {
            appendItem(&result, createItem(current1->coef, current1->exp));
            current1 = current1->next;
        } else if (current1->exp < current2->exp) {
            appendItem(&result, createItem(current2->coef, current2->exp));
            current2 = current2->next;
        } else {
            int sum = current1->coef + current2->coef;
            if (sum != 0) {
                appendItem(&result, createItem(sum, current1->exp));
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // 将剩余项添加到结果中
    while (current1 != NULL) {
        appendItem(&result, createItem(current1->coef, current1->exp));
        current1 = current1->next;
    }
    while (current2 != NULL) {
        appendItem(&result, createItem(current2->coef, current2->exp));
        current2 = current2->next;
    }

    return result;
}

// 打印多项式
void printPoly(PolyItem *poly) {
    PolyItem *current = poly;
    while (current != NULL) {
        printf("%dx^%d ", current->coef, current->exp);
        if (current->next != NULL) {
            printf("+ ");
        }
        current = current->next;
    }
    printf("\n");
}

// 释放多项式内存
void freePoly(PolyItem *poly) {
    PolyItem *current = poly;
    while (current != NULL) {
        PolyItem *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    PolyItem *poly1 = NULL, *poly2 = NULL, *sum = NULL;

    printf("Enter the first polynomial:\n");
    loadPoly(&poly1);
    printf("Enter the second polynomial:\n");
    loadPoly(&poly2);

    sum = addPolynomials(poly1, poly2);
    printf("The sum of the polynomials is:\n");
    printPoly(sum);

    // 释放内存
    freePoly(poly1);
    freePoly(poly2);
    freePoly(sum);

    return 0;
}