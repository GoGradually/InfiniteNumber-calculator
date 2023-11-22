#define ERROR_SIZE 100000

typedef struct __NumberNode {
    int number;
    __NumberNode* next;
    __NumberNode* prev;
} NumberNode;

typedef struct __NumberList {
    NumberNode* head = NULL;
    NumberNode* tail = NULL;
    NumberNode* dot = NULL;
    int operator= 0;
    int integerCnt = 0, fractionCnt = 0;
} NumberList;

typedef struct __NumberListNode {
    NumberList* value;
    NumberListNode* prev;
    NumberListNode* next;
} NumberListNode;

typedef struct __calQueue {
    NumberListNode* qHead = NULL;
    NumberListNode* qTail = NULL;
} queue;

typedef struct __calStack {
    NumberListNode* sTop = NULL;
} stack;

void NumberList_push(NumberList* nl, NumberNode* now);
void queue_push(queue* Q, NumberList* now);
NumberList* queue_pop(queue* Q);
void stack_push(stack* S, NumberList* now);
NumberList* stack_pop(stack* S);
void mallocAssert(void* p);