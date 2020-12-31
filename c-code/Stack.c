#include "Stack.h"

stack* stack_make() {
	stack* newStack = (stack*)malloc(sizeof(stack));
	newStack->topNode = (Node*)malloc(sizeof(Node));
	newStack->topNode->next = newStack->topNode->prev = NULL;
	newStack->length = 0;
	return newStack;
}

void stack_push(stack* stk, int num) {
	Node* newNode = makeNode(num);
	putNode_back(newNode, stk->topNode);
	stk->topNode = newNode;
	stk->length++;
}

int stack_pop(stack* stk) {
	if (stack_empty(stk))
		return ERROR;
	else {
		Node* tmp = stk->topNode;
		int num = tmp->data;
		stk->topNode = stk->topNode->next;
		deleteNode(tmp);
		stk->length--;
		return num;
	}
}

int stack_top(stack* stk) {
	if (stack_empty(stk))
		return ERROR;
	return stk->topNode->data;
}

bool stack_empty(stack* stk) {
	return !(bool)(stk->length);
}

int stack_size(stack* stk) {
	return stk->length;
}