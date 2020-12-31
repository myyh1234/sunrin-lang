// 백준 큐 2 문제로 검증
// http://boj.kr/1035459d42324e0d9e9d2255f32d69c9

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Queue.h"

int main() {
	char order[10];
	int n, num;
	queue* q = queue_make();
	scanf("%d", &n);
	while (n--) {

		rewind(stdin);

		scanf("%s", order);
		if (!strcmp(order, "push")) {
			scanf("%d", &num);
			queue_push(q, num);
		}
		else if (!strcmp(order, "pop"))
			printf("%d\n", queue_pop(q));
		else if (!strcmp(order, "size"))
			printf("%d\n", queue_size(q));
		else if (!strcmp(order, "empty"))
			printf("%d\n", queue_empty(q));
		else if (!strcmp(order, "front"))
			printf("%d\n", queue_front(q));
		else
			printf("%d\n", queue_back(q));
	}
	return 0;
}