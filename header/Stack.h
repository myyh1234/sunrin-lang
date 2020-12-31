#pragma once
#include "LinkedList.h"
#include <stdbool.h>
#define ERROR -1000000007

//c������ ����ó���� ������, �Լ��� ���ϰ� ������� ���� �Ǻ�
//��ó https://stackoverflow.com/questions/2891766/how-to-throw-an-exception-in-c

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