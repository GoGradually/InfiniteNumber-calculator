
#include "infiniteNumberNode.h"

int main() {
    char ch;
    stack *stk = (stack *)malloc(sizeof(stack));
    queue *que = (queue *)malloc(sizeof(queue));
    initializeQueue(que);
    initializeStack(stk);
    int cnt = 0;
    char before = '0';
    NumberListNode *nowNumberListNode = makeNumberListNode();
    while ((ch = (char)getchar()) != '\n') {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            continue;
        } else if (ch >= '0' && ch <= '9') {
            if (before == ')') {
                stack_push_op(stk, que, MUL);
            }
            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);
            initializeNumberNode(temp);
            NumberList_push_back(nowNumberListNode, (int)(ch - '0'), temp);
            cnt++;
        } else if (ch == '.') {
            NumberNode *temp = (NumberNode *)malloc(sizeof(NumberNode));
            mallocAssert(temp);
            initializeNumberNode(temp);
            NumberList_push_back(nowNumberListNode, DOT, temp);
            if (nowNumberListNode->value->dot != NULL) {
                printf("error : Invalid operator!!1%c\n", ch);
                exit(1);
            }
            nowNumberListNode->value->integerCnt = cnt;
            cnt = 0;
            nowNumberListNode->value->dot = temp;
        } else if (ch == '*' || ch == '/' || ch == '+' || ch == '-') {
            if (nowNumberListNode->value->dot == NULL) {
                nowNumberListNode->value->integerCnt = cnt;
            } else {
                nowNumberListNode->value->fractionCnt = cnt;
            }
            cnt = 0;
            queue_push(que, nowNumberListNode);
            nowNumberListNode = makeNumberListNode();
            int op = 0;
            switch (ch) {
                case '*':
                    op = MUL;
                    break;
                case '/':
                    op = DIV;
                    break;
                case '+':
                    op = ADD;
                    break;
                case '-':
                    op = SUB;
                    break;
            }
            stack_push_op(stk, que, op);
        } else if (ch == '(') {
            if (before >= '0' && before <= '9') {
                if (nowNumberListNode->value->dot == NULL) {
                    nowNumberListNode->value->integerCnt = cnt;
                } else {
                    nowNumberListNode->value->fractionCnt = cnt;
                }
                cnt = 0;
                queue_push(que, nowNumberListNode);
                nowNumberListNode = makeNumberListNode();

                stack_push_op(stk, que, MUL);
            }
            stack_push_op(stk, que, OPEN_BRACKET);
        } else if (ch == ')') {
            if (nowNumberListNode->value->dot == NULL) {
                nowNumberListNode->value->integerCnt = cnt;
            } else {
                nowNumberListNode->value->fractionCnt = cnt;
            }
            cnt = 0;
            queue_push(que, nowNumberListNode);
            nowNumberListNode = makeNumberListNode();

            NumberListNode *temp;
            while ((temp = stack_pop(stk))->value->op != OPEN_BRACKET) {
                queue_push(que, temp);
                if (stk->sTop == NULL) {
                    printf("error : Invalid Operation2!!\n");
                    exit(1);
                }
            }
            NumberListNode_Clear(temp);
            cnt = 0;
        } else {
            printf("error : Invalid operator3!!%c\n", ch);
            exit(1);
        }
        before = ch;
    }

    if (nowNumberListNode->value->dot == NULL) {
        nowNumberListNode->value->integerCnt = cnt;
    } else {
        nowNumberListNode->value->fractionCnt = cnt;
    }
    queue_push(que, nowNumberListNode);

    while (stk->sTop !=NULL) queue_push(que, stack_pop(stk));

    stack* operand = (stack*)malloc(sizeof(stack));
    mallocAssert(operand);
    initializeStack(operand);
    NumberListNode *pprev = NULL, *prev = NULL;
    while (que->qHead != NULL) {
        NumberListNode *now = queue_pop(que);
        print_NumberListNode(now);
        if (now->value->op == 0) {
            stack_push(operand, now);
        } else {
            prev = stack_pop(operand);
            pprev = stack_pop(operand);
            if (prev == NULL || pprev == NULL) {
                printf("error : Invalid Operation5!!\n");
                exit(1);
            }
            int op = now->value->op;
            switch (op) {
                case ADD:
                    stack_push(operand, add(prev, pprev));
                    break;
                case SUB:
                    stack_push(operand, subtract(prev, pprev));
                    break;
                case MUL:
                    stack_push(operand, multiply(prev, pprev));
                    break;
                case DIV:
                    stack_push(operand, divide(prev, pprev));
                    break;
            }
            pprev = NULL;
        }
    }
    if (pprev != NULL) {
        printf("error : Invalid Operation6!!\n");
        exit(1);
    }
    print_NumberListNode(prev);
    return 0;
}
