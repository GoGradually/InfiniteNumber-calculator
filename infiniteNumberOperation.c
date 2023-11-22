#include "infiniteNumberOperation.h"

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
    /*
     *  write the code
     */
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
