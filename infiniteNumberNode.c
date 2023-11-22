void NumberList_push(NumberList* nl, int val, NumberNode* now) {
    now->number = val;
    nl->tail->next = now;
    now->prev = nl->tail;
    nl->tail = now;
}
void queue_push(queue* Q, NumberList* now) {
    NumberListNode* nowNode = (NumberListNode*)malloc(sizeof(NumberListNode));
    mallocAssert(nowNode);
    nowNode->value = now;
    if (Q->qHead == NULL) {
        Q->qHead = nowNode;
        Q->qTail = nowNode;
    } else {
        Q->qTail->next = nowNode;
        nowNode->prev = Q->qTail;
        Q->qTail = nowNode;
    }
}

NumberList* queue_pop(queue* Q) {
    if (Q->qHead == NULL) {
        printf("error : empty Queue pop!!\n");
        exit(1);
    }
    NumberList* ret = Q->qHead->value;
    NumberListNode* temp = Q->qHead;
    if (Q->qHead == qTail) {
        qTail = NULL;
    }
    Q->qHead = Q->qHead->next;
    free(temp);
    if (Q->qHead != NULL) Q->qHead->prev = NULL;
    return ret;
}

void stack_push(stack* S, NumberList* now) {
    NumberListNode* nowNode = (NumberListNode*)malloc(sizeof(NumberListNode));
    mallocAssert(nowNode);
    nowNode->value = now;
    if (S->sTop == NULL) {
        S->sTop = nowNode;
    } else {
        S->sTop->next = nowNode;
        nowNode->prev = S->sTop;
        S->sTop = nowNode;
    }
}

NumberList* stack_pop(stack* S) {
    if (S->sTop == NULL) {
        printf("error : empty stack pop!!\n");
        exit(1);
    }
    NumberList* ret = S->sTop->value;
    NumberListNode* temp = S->sTop;
    S->sTop = S->sTop->prev;
    free(temp);
    if (S->sTop != NULL) S->sTop->next = NULL;
    return ret;
}

void mallocAssert(void* p) {
    if (p == NULL) {
        printf("error : memory exceed!!\n");
        exit(1);
    }
}