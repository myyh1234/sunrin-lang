// 백준 스택 문제로 검증
// http://boj.kr/90fc7f1279d84d97ac3f2e33a8977b55

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Stack.h"

int main() {
	char order[10];
	int n, num;
	stack* stk = stack_make();
	scanf("%d", &n);
	while (n--) {

		rewind(stdin);

		scanf("%s", order);
		if (!strcmp(order, "push")) {
			scanf("%d", &num);
			stack_push(stk, num);
		}
		else if (!strcmp(order, "pop"))
			printf("%d\n", stack_pop(stk));
		else if (!strcmp(order, "size"))
			printf("%d\n", stack_size(stk));
		else if (!strcmp(order, "empty"))
			printf("%d\n", stack_empty(stk));
		else
			printf("%d\n", stack_top(stk));
	}
	return 0;
}