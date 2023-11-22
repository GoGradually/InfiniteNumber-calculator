#define ERROR_SIZE 100000

typedef struct __NumberNode {
    int number;
    __NumberNode* next;
    __NumberNode* prev;
} NumberNode;

// directionless Number list
typedef struct __NumberList {
    NumberNode* head = NULL;
    NumberNode* tail = NULL;
    NumberNode* dot = NULL;
    int op = 0;
    int integerCnt = 0, fractionCnt = 0;
} NumberList;

// A structure providing directionality for concatenating elements in a list of
// real numbers, both front and back
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

void NumberList_push_back(NumberListNode* nl, int val, NumberNode* now);
void NumberList_push_front(NumberListNode* nl, int val, NumberNode* now);
NumberListNode* makeNumberListNode();
void queue_push(queue* Q, NumberListNode* nowNode);
NumberListNode* queue_pop(queue* Q);
void stack_push(stack* S, NumberListNode* now);
NumberListNode* stack_pop(stack* S);
void NumberList_Clear(NumberList* nl);
void NumberListNode_Clear(NumberListNode* nln);
void stack_push_op(stack* S, queue* Q, int opInput);
void mallocAssert(void* p);
void print_NumberListNode(NumberListNode* nln);