#include "infiniteNumberNode.h"

void initializeQueue(queue* q) {
    q->qHead = NULL;
    q->qTail = NULL;
}
void initializeStack(stack* s) { s->sTop = NULL; }
void initializeNumberNode(NumberNode* node) {
    node->number = 0;
    node->prev = NULL;
    node->next = NULL;
}
void initializeNumberList(NumberList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->dot = NULL;
    list->op = 0;
    list->integerCnt = 0;
    list->fractionCnt = 0;
}
void initializeNumberListNode(NumberListNode* node) {
    node->prev = NULL;
    node->next = NULL;
    node->value = NULL;
}
void NumberList_push_back(NumberListNode* nln, int val, NumberNode* now) {
    now->number = val;
    if (nln->value->tail == NULL) {
        nln->value->head = now;
        nln->value->tail = now;
    }  
    else {
        nln->value->tail->next = now;
        if (now == NULL) {
            printf("error : NULLNumber pushed in NumberList\n");
            exit(1);
        }
        now->prev = nln->value->tail;
        nln->value->tail = now;
    }
}
void NumberList_push_front(NumberListNode* nln, int val, NumberNode* now) {
    now->number = val;
    if (nln->value->head == NULL) {
        nln->value->head = now;
        nln->value->tail = now;
    }
    else {
        nln->value->head->prev = now;
        if (now == NULL) {
            printf("error : NULLNumber pushed in NumberList\n");
            exit(1);
        }
        now->next = nln->value->head;
        nln->value->head = now;
    }
}
NumberListNode* makeNumberListNode() {
    NumberList* now = (NumberList*)malloc(sizeof(NumberList));
    mallocAssert(now);
    initializeNumberList(now);
    NumberListNode* nowNode = (NumberListNode*)malloc(sizeof(NumberListNode));
    mallocAssert(nowNode);
    initializeNumberListNode(nowNode);
    nowNode->value = now;
    return nowNode;
}
void queue_push(queue* que, NumberListNode* nowNode) {
    if (que->qHead == NULL) {
        que->qHead = nowNode;
        que->qTail = nowNode;
    } else {
        que->qTail->next = nowNode;
        if (nowNode == NULL) {
            printf("error : NULLList pushed in queue\n");
            exit(1);
        }
        nowNode->prev = que->qTail;
        que->qTail = nowNode;
    }
}

NumberListNode* queue_pop(queue* que) {
    if (que->qHead == NULL) {
        printf("error : empty Queue pop!!\n");
        exit(1);
    }
    NumberListNode* ret = que->qHead;
    if (que->qHead == que->qTail) {
        que->qTail = NULL;
    }
    que->qHead = que->qHead->next;
    if (que->qHead != NULL) que->qHead->prev = NULL;
    ret->next = NULL;
    return ret;
}

void stack_push(stack* stk, NumberListNode* nowNode) {
    if (stk->sTop == NULL) {
        stk->sTop = nowNode;
    } else {
        stk->sTop->next = nowNode;
        if (nowNode == NULL) {
            printf("error : NULLList pushed in stack\n");
            exit(1);
        }
        nowNode->prev = stk->sTop;
        stk->sTop = nowNode;
    }
}

NumberListNode* stack_pop(stack* stk) {
    if (stk->sTop == NULL) {
        printf("error : empty stack pop!!\n");
        exit(1);
    }
    NumberListNode* ret = stk->sTop;
    stk->sTop = stk->sTop->prev;
    if (stk->sTop != NULL) stk->sTop->next = NULL;
    ret->prev = NULL;
    return ret;
}

void mallocAssert(void* p) {
    if (p == NULL) {
        printf("error : memory exceed!!\n");
        exit(1);
    }
}
void NumberList_Clear(NumberList* nl) {
    while (nl->head != NULL) {
        NumberNode* temp = nl->head;
        nl->head = nl->head->next;
        free(temp);
    }
    free(nl);
}
void NumberListNode_Clear(NumberListNode* nln) {
    NumberList_Clear(nln->value);
    free(nln);
}
void stack_push_op(stack* stk, queue* que, int opInput) {
    while (stk->sTop != NULL && (stk->sTop->value->op) != OPEN_BRACKET &&
           (stk->sTop->value->op) / 2 >= opInput / 2) {
        queue_push(que, stack_pop(stk));
    }
    NumberList* now = (NumberList*)malloc(sizeof(NumberList));
    mallocAssert(now);
    initializeNumberList(now);
    now->op = opInput;
    NumberListNode* node = makeNumberListNode();
    node->value = now;
    stack_push(stk, node);
}

void print_NumberListNode(NumberListNode* nln) {
    if (nln == NULL) {
        printf("error : number is empty\n");
        exit(1);
    }
    if (nln->value == NULL) {
        printf("error : NumberList is empty\n");
        exit(1);
    }
    if (nln->value->op == 0) {
        NumberNode* now = nln->value->head;
        while (now != NULL) {
            if (now->number == DOT) {
                printf(".");
            }
            else {
                printf("%d", now->number);
            }
            now = now->next;
        }
    }
    else {
        printf("op : %d ", nln->value->op);
    }
    printf("\n");
}

/*
 * divide by 2
 * coded by 한준호
 */

void divide_by_2(NumberListNode* val) {}

/*
 * add operation
 * The result of the calculation of val1 + val2 is stored in the
 * NumberListNode ret, and ret is returned.
 * coded by 김현식
 */
NumberListNode* add(NumberListNode* val1, NumberListNode* val2) {
    NumberListNode* ret = makeNumberListNode();
    /*
     *  write the code
     */
    NumberListNode_Clear(val1);
    NumberListNode_Clear(val2);
    return ret;
}
/*
 * subtract operation
 * The result of the calculation of val1 - val2 is stored in the
 * NumberListNode ret, and ret is returned.
 * coded by 조신붕, 후상우
 */
NumberListNode* subtract(NumberListNode* val1, NumberListNode* val2) {
    NumberListNode* ret = makeNumberListNode();
    
    NumberListNode* current1 = val1;//Pointer used to traverse the first linked list
    NumberListNode* current2 = val2;//Pointer for traversing the second linked list
    NumberListNode* currentResult = ret;//Pointer used to traverse the result list
    int borrow = 0;// Used to track borrowing status

    // Iterate over numbers
    while (current1 != NULL || current2 != NULL) {
        // Gets a number, using 0 if node is NULL
        int digit1 = (current1 != NULL) ? current1->value->head->number : 0;
        int digit2 = (current2 != NULL) ? current2->value->head->number : 0;

        // Subtract numbers and handle borrowing
        int resultDigit = digit1 - digit2 - borrow;
        if (resultDigit < 0) {
            resultDigit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        // Set the result number in the current node
        currentResult->value->head->number = resultDigit;

        // move to next node
        if (current1 != NULL) current1 = current1->next;
        if (current2 != NULL) current2 = current2->next;

        // Create a new node for the next result number
        if (current1 != NULL || current2 != NULL) {
            currentResult->next = makeNumberListNode();
            currentResult = currentResult->next;
        }
    }

    
    NumberListNode_Clear(val1);
    NumberListNode_Clear(val2);
    return ret;
}

/*
 * multiply operation
 * coded by 한준호
 */
NumberListNode* multiply(NumberListNode* val1, NumberListNode* val2) {
    NumberListNode* ret = makeNumberListNode();

    NumberListNode_Clear(val1);
    NumberListNode_Clear(val2);
    return ret;
}

/*
 * divide operation
 * coded by 한준호
 */
NumberListNode* divide(NumberListNode* val1, NumberListNode* val2) {
    NumberListNode* ret = makeNumberListNode();

    NumberListNode_Clear(val1);
    NumberListNode_Clear(val2);
    return ret;
}
