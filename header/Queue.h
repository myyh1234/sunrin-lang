#pragma once
#include "LinkedList.h"
#include <stdbool.h>
#define ERROR -1000000007

typedef struct Queue {
	Node* frontNode, * backNode;
	int length;
} queue;

queue* queue_make();
void queue_push(queue* q, int num);
int queue_pop(queue* q);
int queue_front(queue* q);
int queue_back(queue* q);
bool queue_empty(queue* q);
int queue_size(queue* q);