typedef struct __Node {
    int number;
    ll pos;
    __Node* next;
    __Node* prev;
} Node;

typedef struct __NumberList {
    Node* head = NULL;
    Node* tail = NULL;
    Node* dot = NULL;
    int operator= 0;
    int integerCnt = 0, fractionCnt = 0;
} NumberList;

typedef struct __calQueue {
    NumberList* qHead = NULL;
    NumberList* qTail = NULL;
} queue;