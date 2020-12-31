#include "LinkedList.h"

Node* makeNode(int num) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = num;
	newNode->prev = newNode->next = NULL;
	return newNode;
}

void deleteNode(Node* nowNode) {
	if (nowNode->prev != NULL)
		nowNode->prev->next = nowNode->next;
	if (nowNode->next != NULL)
		nowNode->next->prev = nowNode->prev;
	free(nowNode);
}

void putNode_front(Node* nowNode, Node* prevNode) {
	nowNode->prev = prevNode;
	nowNode->next = prevNode->next;
	if (prevNode->next != NULL)
		prevNode->next->prev = nowNode;
	prevNode->next = nowNode;
}

void putNode_back(Node* nowNode, Node* nextNode) {
	nowNode->next = nextNode;
	nowNode->prev = nextNode->prev;
	if (nextNode->prev != NULL)
		nextNode->prev->next = nowNode;
	nextNode->prev = nowNode;
}