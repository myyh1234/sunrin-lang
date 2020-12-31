#pragma once
#include <malloc.h>
typedef struct List {
	int data;
	struct List* prev, * next;
} Node;

Node* makeNode(int num);
void deleteNode(Node* nowNode);
void putNode_front(Node* nowNode, Node* prevNode);
void putNode_back(Node* nowNode, Node* nextNode);