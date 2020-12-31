#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Stack.h"

// 백준을 통한 검증 - http://boj.kr/35ef7794b37e4f22a55b9106c0382547

int main() {
	char order[10];
	int n, num;
	stack* stk = makeStack();
	scanf("%d", &n);
	while (n--) {

		rewind(stdin);

		scanf("%s", order);
		if (!strcmp(order, "push")) {
			scanf("%d", &num);
			push(stk, num);
		}
		else if (!strcmp(order, "pop"))
			printf("%d\n", pop(stk));
		else if (!strcmp(order, "size"))
			printf("%d\n", size(stk));
		else if (!strcmp(order, "empty"))
			printf("%d\n", empty(stk));
		else
			printf("%d\n", top(stk));
	}
	return 0;
}