#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infiniteNumberNode.h"

int main() {
    char ch;
    stack stk = (stack *)malloc(sizeof(stack));
    queue *q = (queue *)malloc(sizeof(queue));
    int cnt = 0;
    NumberList *nowNumber = (NumberList *)malloc(sizeof(NumberList));
    mallocAssert(nowNumber);
    while ((ch = getchar() != '\0')) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            continue;
        } else if (ch >= '0' && ch <= '9') {
            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);
            NumberList_push(nowNumber, (int)(ch - '0'), temp);
            cnt++;
        } else if (ch == '.') {
            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);
            NumberList_push(nowNumber, -1000000000, temp);
            if (nowNumber->dot != NULL) {
                printf("error : Invalid operator!!\n");
                exit(1)
            }
            nowNumber->integerCnt = cnt;
            cnt = 0;
            nowNumber->dot = temp;
        } else if (ch == '*' || ch == '/') {
            if (nowNumber->dot == NULL) {
                nowNumber->integerCnt = cnt;
            } else {
                nowNumber->fractionCnt = cnt;
            }
            cnt = 0;

            queue_push(q, nowNumber);
            nowNumber = (NumberList *)malloc(sizeof(NumberList));
            mallocAssert(nowNumber);

            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);

            queue_push(q, nowNumber);
            nowNumber = (NumberList *)malloc(sizeof(NumberList));
            mallocAssert(nowNumber);

        } else if (ch == '+' || ch == '-') {
            if (nowNumber->dot == NULL) {
                nowNumber->integerCnt = cnt;
            } else {
                nowNumber->fractionCnt = cnt;
            }
            cnt = 0;

            queue_push(q, nowNumber);
            nowNumber = (NumberList *)malloc(sizeof(NumberList));
            mallocAssert(nowNumber);

            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);
        } else if (ch == '(') {
        } else if (ch == ')') {
        } else {
            printf("error : Invalid Operator!\n");
            exit(1);
        }
    }
    if (nowNumber->dot == NULL) {
        nowNumber->integerCnt = cnt;
    } else {
        nowNumber->fractionCnt = cnt;
    }
    queue_push(q, nowNumber);
    while (q->qHead == q->qTail) {
    }
}
