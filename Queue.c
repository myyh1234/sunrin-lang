#include "Queue.h"

queue* queue_make() {
	queue* newQueue = (queue*)malloc(sizeof(queue));
	newQueue->backNode = (Node*)malloc(sizeof(Node));
	newQueue->backNode->next = NULL;
	newQueue->frontNode = (Node*)malloc(sizeof(Node));
	newQueue->frontNode->prev = NULL;
	putNode_back(newQueue->backNode, newQueue->frontNode);
	newQueue->length = 0;
	return newQueue;
}

void queue_push(queue* q, int num) {
	Node* newNode = makeNode(num);
	putNode_front(newNode, q->backNode);
	q->length++;
}

int queue_pop(queue* q) {
	if (queue_empty(q))
		return ERROR;
	else {
		int num = q->frontNode->prev->data;
		deleteNode(q->frontNode->prev);
		q->length--;
		return num;
	}
}

int queue_front(queue* q) {
	if (queue_empty(q))
		return ERROR;
	return q->frontNode->prev->data;
}

int queue_back(queue* q) {
	if (queue_empty(q))
		return ERROR;
	return q->backNode->next->data;
}

bool queue_empty(queue* q) {
	return !(bool)(q->length);
}

int queue_size(queue* q) {
	return q->length;
}