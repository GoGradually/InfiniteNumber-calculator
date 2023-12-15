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
    list->sign = 1;
}
void initializeNumberListNode(NumberListNode* node) {
    node->prev = NULL;
    node->next = NULL;
    node->value = NULL;
}
void NumberList_push_back(NumberList* nl, int val, NumberNode* now) {
    now->number = val;
    if (nl->value->tail == NULL) {
        nl->value->head = now;
        nl->value->tail = now;
    } else {
        nl->value->tail->next = now;
        if (now == NULL) {
            printf("error : NULLNumber pushed in NumberList\n");
            exit(1);
        }
        now->prev = nl->value->tail;
        nl->value->tail = now;
    }
}
void NumberList_push_front(NumberList* nl, int val, NumberNode* now) {
    now->number = val;
    if (nl->value->head == NULL) {
        nl->value->head = now;
        nl->value->tail = now;
    } else {
        nl->value->head->prev = now;
        if (now == NULL) {
            printf("error : NULLNumber pushed in NumberList\n");
            exit(1);
        }
        now->next = nl->value->head;
        nl->value->head = now;
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

NumberNode* makeNumberNode() {
    NumberNode* now = (NumberNode*)malloc(sizeof(NumberNode));
    mallocAssert(now);
    initializeNumberNode(now);
    return now;
}

void NumberList_push_dot(NumberList* nl) {
    NumberNode* temp = makeNumberNode();
    NumberList_push_back(nowNumberListNode->value, DOT, temp);
    nowNumberListNode->value->dot = temp;
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
            } else {
                printf("%d", now->number);
            }
            now = now->next;
        }
    } else {
        printf("op : %d ", nln->value->op);
    }
    printf("\n");
}

/*
 * divide by 2
 * coded by 한준호


void divide_by_2(NumberListNode* val) {}
*/

/*
 * add operation
 * The result of the calculation of val1 + val2 is stored in the
 * NumberListNode ret, and ret is returned.
 * coded by 김현식, 이동철
 */
NumberListNode* add(NumberListNode* val1, NumberListNode* val2) {
    NumberListNode* ret = makeNumberListNode();
    ret->value->sign = val1->value->sign;
    NumberNode* i_current1 =
        val1->value->dot->prev;  // Pointer used to traverse the integer part of
                                 // linked list(val1,val2)
    NumberNode* i_current2 = val2->value->dot->prev;

    NumberNode* f_current1 =
        val1->value->dot->next;  // Pointer used to traverse the decimal part of
                                 // linked list(val1,val2)
    NumberNode* f_current2 = val2->value->dot->next;

    NumberNode* now;  // Pointer used to make NumberNode for linked list(ret)

    int carry = 0;  // number used to carry

    while (f_current1 != NULL ||
           f_current2 !=
               NULL) {  // loop used to calculate decimal part of linked
                        // list(val1, val2) and add calculate result to linked
                        // list(ret) ex) 123.45+123.35, calculate result of this
                        // loop is 710(decimal part)
        int float1 = (f_current1 != NULL) ? f_current1->number : 0;
        int float2 = (f_current2 != NULL) ? f_current2->number : 0;

        int sum = float1 + float2;

        now = makeNumberNode();
        NumberList_push_back(ret->value, sum, now);

        if (f_current1 != NULL) f_current1 = f_current1->next;
        if (f_current2 != NULL) f_current2 = f_current2->next;
    }

    NumberNode* r_current =
        ret->value->tail;  // Pointer used to traverse the decimal part of
                           // linked list(ret)

    while (r_current != NULL) {  // loop used to carry decimal part of linked
                                 // list(ret) ex) 123.45+123.35, calculate
                                 // result of this loop is 80(decimal part)
        int sum = r_current->number + carry;
        carry = sum / 10;
        r_current->number = (sum) % 10;

        r_current = r_current->prev;
    }

    now = makeNumberNode();
    NumberList_push_front(
        ret->value, DOT,
        now);  // add dot to linked list(ret) ex) 123.45+123.35,
               // calculate result of this loop is .80(decimal part)
    ret->value->dot = ret->value->head;

    while (i_current1 != NULL || i_current2 != NULL ||
           carry != 0) {  // loop used to calculate and carry integer part of
                          // linked list(val1, val2) and add calculate result to
                          // linked list(ret)
        int digit1 = (i_current1 != NULL) ? i_current1->number
                                          : 0;  // ex) 123.45+123.35, calculate
                                                // result of this loop is 246.80
        int digit2 = (i_current2 != NULL) ? i_current2->number : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        now = makeNumberNode();
        NumberList_push_front(ret->value, sum % 10, now);

        if (i_current1 != NULL) i_current1 = i_current1->prev;
        if (i_current2 != NULL) i_current2 = i_current2->prev;
    }

    while (ret->value->tail->number == 0 ||
           ret->value->tail ==
               ret->value->dot) {  // loop used to free zero value at ending of
                                   // calculate result(ret) ex) 123.45+123.35,
                                   // calculate result of this loop is 246.8
        NumberNode* temp = ret->value->tail;
        ret->value->tail = ret->value->tail->prev;
        ret->value->tail->next = NULL;
        if (temp == ret->value->dot) {
            ret->value->dot = NULL;
            free(temp);
            break;
        }
        free(temp);
    }

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
    ret->value->sign = val1->value->sign;

    NumberListNode* i_current1 =
        val1->value->dot
            ->prev;  // Pointer used to traverse the first linked list
    NumberListNode* i_current2 =
        val2->value->dot
            ->prev;  // Pointer for traversing the second linked list
    NumberListNode* f_current1 = val1->value->dot->next;
    NumberListNode* f_current2 =
        val2->value->dot->next;  // Pointer used to traverse the result list
    NumberNode* now;
    int borrow = 0;  // Used to track borrowing status

    // Iterate over numbers
    while (f_current1 != NULL || f_current2 != NULL) {
        // Gets a number, using 0 if node is NULL
        int float1 = (f_current1 != NULL) ? f_current1->number : 0;
        int float2 = (f_current2 != NULL) ? f_current2->number : 0;
        int diff = 10 + float1 - float2;

        now = makeNumberNode();
        NumberList_push_back(ret->value, diff, now);

        if (f_current1 != NULL) f_current1 = f_current1->next;
        if (f_current2 != NULL) f_current2 = f_current2->next;
    }

    NumberNode* r_current = ret->value->tail;

    while (r_current != NULL) {
        int diff = r_current->number - borrow;

        if (diff < 10) {
            borrow = 1;
        } else {
            diff = diff % 10;
            borrow = 0;
        }

        r_current->number = diff;

        r_current = r_current->prev;
    }

    now = makeNumberNode();
    NumberList_push_front(ret->value, DOT, now);
    ret->value->dot = ret->value->head;

    if (ret->value->head->number == 0 && ret->value->dot == ret->value->tail) {
        ret->value->sign = 1;
    }

    while (i_current1 != NULL) {
        int digit1 = (i_current1 != NULL) ? i_current1->number : 0;
        int digit2 = (i_current2 != NULL) ? i_current2->number : 0;

        int diff = 10 + digit1 - digit2 - borrow;
        if (diff < 10) {
            borrow = 1;
        } else {
            borrow = 0;
        }

        now = makeNumberNode();
        NumberList_push_front(ret->value, diff % 10, now);

        if (i_current1 != NULL) i_current1 = i_current1->prev;
        if (i_current2 != NULL) i_current2 = i_current2->prev;
    }
    // Remove leading zeros
    while (ret->value->head->number == 0 &&
           ret->value->head != ret->value->dot->prev) {
        NumberNode* temp = ret->value->head;
        ret->value->head = ret->value->head->next;
        ret->value->head->prev = NULL;
        if (temp == ret->value->dot->prev) {
            free(temp);
            break;
        }
        free(temp);
    }

    while (ret->value->tail->number == 0 &&
           ret->value->tail != ret->value->dot) {
        NumberNode* temp = ret->value->tail;
        ret->value->tail = ret->value->tail->prev;
        ret->value->tail->next = NULL;
        if (temp == ret->value->dot) {
            ret->value->dot = NULL;
            free(temp);
            break;
        }
        free(temp);
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

int compareAbsoluteValue(NumberListNode* val1, NumberListNode* val2) {
    NumberNode* i_current1 =
        val1->value->dot->prev;  // Pointer used to traverse the integer part of
                                 // linked list(val1,val2)
    NumberNode* i_current2 = val2->value->dot->prev;

    NumberNode* f_current1 =
        val1->value->dot->next;  // Pointer used to traverse the decimal part of
                                 // linked list(val1,val2)
    NumberNode* f_current2 = val2->value->dot->next;

    int ret = 0;
    while (i_current1 != NULL && i_current2 != NULL) {
        if (i_current1->number > i_current2->number) {
            ret = 1
        } else if (i_current1->number < i_current2->number) {
            ret = -1;
        }
        i_current1 = i_current1->prev;
        i_current2 = i_current2->prev;
    }
    if (i_current1 == NULL && i_current2 != NULL) {
        ret = -1;  // val1 < val2
    }
    if (i_current1 != NULL && i_current2 == NULL) {
        ret = 1;  // val1 > val2
    }
    if (ret != 0) return ret;

    while (f_current1 != NULL && f_current2 != NULL && ret == 0) {
        if (f_current1->number > f_current2->number) {
            ret = 1
        } else if (f_current1->number < f_current2->number) {
            ret = -1;
        }
        f_current1 = f_current1->next;
        f_current2 = f_current2->next;
    }
    if (ret != 0) return ret;

    if (f_current1 == NULL && f_current2 != NULL) {
        ret = -1;  // val1 < val2
    }
    if (f_current1 != NULL && f_current2 == NULL) {
        ret = 1;  // val1 > val2
    }
    return ret;
}