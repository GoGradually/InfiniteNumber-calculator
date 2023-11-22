#include "infiniteNumberNode.h"
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define OPEN_BRACKET 1
#define DOT -1000000000
void divide_by_2(NumberList* val);
NumberList* add(NumberList* val1, NumberList* val2);
NumberList* subtract(NumberList* val1, NumberList* val2);
NumberList* multiply(NumberList* val1, NumberList* val2);
NumberList* divide(NumberList* val1, NumberList* val2);