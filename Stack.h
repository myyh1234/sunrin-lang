#pragma once
#include "LinkedList.h"
#include <stdbool.h>
#define ERROR -1000000007

//c에서는 예외처리가 없으며, 함수의 리턴값 등등으로 예외 판별
//출처 https://stackoverflow.com/questions/2891766/how-to-throw-an-exception-in-c

typedef struct Stack {
	Node* topNode;
	int length;
} stack;

stack* stack_make();
void stack_push(stack* stk, int num);
int stack_pop(stack* stk);
int stack_top(stack* stk);
bool stack_empty(stack* stk);
int stack_size(stack* stk);