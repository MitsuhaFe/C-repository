#include <stdio.h>
#include <stdlib.h>


typedef struct PolyItem {
    int coef;
    int exp;
    struct PolyItem *next;
} PolyItem;


PolyItem* createItem(int coef, int exp) {
    PolyItem *item = (PolyItem*)malloc(sizeof(PolyItem));
    if (item != NULL) {
        item->coef = coef;
        item->exp = exp;
        item->next = NULL;
    }
    return item;
}


void appendItem(PolyItem **poly, int coef, int exp) {
    PolyItem *newItem = createItem(coef, exp);
    if (newItem == NULL) {
        printf("内存分配失败。\n");
        exit(1);
    }
    if (*poly == NULL) {
        *poly = newItem;
    } else {
        PolyItem *current = *poly;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}


PolyItem* addPolynomials(PolyItem *poly1, PolyItem *poly2) {
    PolyItem *result = NULL;
    PolyItem *current1 = poly1;
    PolyItem *current2 = poly2;
    while (current1 != NULL && current2 != NULL) {
        if (current1->exp > current2->exp) {
            appendItem(&result, current1->coef, current1->exp);
            current1 = current1->next;
        } else if (current1->exp < current2->exp) {
            appendItem(&result, current2->coef, current2->exp);
            current2 = current2->next;
        } else {
            int sumCoef = current1->coef + current2->coef;
            if (sumCoef != 0) {
                appendItem(&result, sumCoef, current1->exp);
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        appendItem(&result, current1->coef, current1->exp);
        current1 = current1->next;
    }
    while (current2 != NULL) {
        appendItem(&result, current2->coef, current2->exp);
        current2 = current2->next;
    }
    return result;
}

void printPolynomial(PolyItem *poly) {
    PolyItem *current = poly;
    while (current != NULL) {
        printf("%dx^%d", current->coef, current->exp);
        if (current->next != NULL) {
            printf(" + ");
        }
        current = current->next;
    }
    printf("\n");
}


int main() {
    PolyItem *poly1 = NULL;
    PolyItem *poly2 = NULL;
    int coef, exp, numTerms;

    printf("输入第一个多项式的项数：");
    scanf("%d", &numTerms);
    for (int i = 0; i < numTerms; ++i) {
        printf("输入第 %d 项的系数和指数：", i + 1);
        scanf("%d %d", &coef, &exp);
        appendItem(&poly1, coef, exp);
    }
    printf("输入第二个多项式的项数：");
    scanf("%d", &numTerms);
    for (int i = 0; i < numTerms; ++i) {
        printf("输入第 %d 项的系数和指数：", i + 1);
        scanf("%d %d", &coef, &exp);
        appendItem(&poly2, coef, exp);
    }

    PolyItem *result = addPolynomials(poly1, poly2);

    printf("两个多项式相加的结果是：");
    printPolynomial(result);

    return 0;
}