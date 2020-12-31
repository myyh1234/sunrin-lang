#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"
#define and &&
#define or ||

int count_riin(char* start);
int count_suun(char* start);
int main() {
	queue* q[2] = { queue_make(), queue_make() };
	stack* stk[7], * pair = stack_make();
	char tmp[2005], ** cmd; // 한 줄에 최대 1000글자 들어갈 수 있음
	int got_num, pair_chk = 0, now_idx = 0, now_space, error, error_line = 0;
	// -1 : 종료 코드가 없음, 1 : 빈 스택 / 큐에 연산을 시도함, 2 : 선 / 린 짝이 맞지 않음, 3 : 0으로 나눔

	FILE* code = fopen("code.txt", "r");
	FILE* out = fopen("output.txt", "w");
	for (int i = 0; i < 7; i++)
		stk[i] = stack_make();

	//------------- 코드 확인 --------------
	while (true) {
		now_idx++;
		error = fgets(tmp, sizeof tmp, code);;
		if (error == NULL) {
			error = -1;
			break;
		}
		error = 0;
		if (!strcmp(tmp, "의 자랑 1학년 4반!") or !strcmp(tmp, "의 자랑 1학년 4반!\n"))
			break;
		if (!strcmp(tmp, "선"))
			pair_chk++;
		else if (!strcmp(tmp, "린")) {
			pair_chk--;
			if (pair_chk < 0) {
				error = 2;
				break;
			}
		}
	}
	// ----------- 에러 체크 ------------
	if (pair_chk)
		error = 2;
	if (error) {
		if (error == -1)
			fputs("ERROR -1 : 종료 코드 \'의 자랑 1학년 4반!\' 을 찾을 수 없습니다.", out);
		else
			fputs("ERROR 2 : \'선\' 과 \'린\' 의 짝이 맞지 않습니다.", out);
	}
	else {
		// --------------- 런타임 --------------

		// 명령어 받을 메모리 할당
		cmd = malloc(sizeof(char*) * now_idx);
		cmd[0] = malloc(sizeof(char) * 2005 * now_idx);
		for (int i = 1; i < now_idx; i++)
			cmd[i] = cmd[i - 1] + 2005;

		rewind(code); // 코드 처음부터 다시 읽으며 command에 저장

		for (int i = 0; i < now_idx; i++) {
			fgets(cmd[i], 2005, code);
			if (cmd[i][strlen(cmd[i]) - 1] == '\n')
				cmd[i][strlen(cmd[i]) - 1] = '\0';
		}

		now_idx = -1;
		now_space = 0;
		pair_chk = 0; // '선'에서 top이 0일 때 대응되는 '린'을 찾기 위해 사용
		while (true) {
			now_idx++;
			if (now_idx == 2)
				now_idx += 0;
			if (now_idx == 67)
				now_idx += 0;
			if (pair_chk) {
				if (!strcmp(cmd[now_idx], "선"))
					pair_chk++;
				else if (!strcmp(cmd[now_idx], "린"))
					pair_chk--;
				continue;
			}

			if (!strcmp(cmd[now_idx], "의 자랑 1학년 4반!"))
				break;

			if (!strcmp(cmd[now_idx], "선선")) { // 정수 입력받기
				printf("정수를 입력하세요 : ");
				scanf("%d", &got_num);
				if (now_space < 7) // stack이라면
					stack_push(stk[now_space], got_num);
				else // queue라면
					queue_push(q[now_space - 7], got_num);
			}

			else if (!strcmp(cmd[now_idx], "린린")) { // 문자 출력하기
				int will_print;
				if (now_space < 7) // stack이라면
					will_print = stack_top(stk[now_space]);
				else // queue라면
					will_print = queue_front(q[now_space - 7]);
				if (will_print == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					fprintf(out, "%c", (char)will_print);
			}

			else if (!strcmp(cmd[now_idx], "선선린린")) { // 숫자 출력하기
				int will_print;
				if (now_space < 7) // stack이라면
					will_print = stack_top(stk[now_space]);
				else // queue라면
					will_print = queue_front(q[now_space - 7]);
				if (will_print == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					fprintf(out, "%d", will_print);
			}

			else if (!strcmp(cmd[now_idx], "린선")) { // 하나 뽑아 버리기
				if (now_space < 7) // stack이라면
					error = stack_pop(stk[now_space]);
				else // queue라면
					error = queue_pop(q[now_space - 7]);
				if (error == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					error = 0;
			}

			else if (!strcmp(cmd[now_idx], "서선")) { // 수 2개 뽑아 더하고 넣기
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], a + b);
					else // queue라면
						queue_push(q[now_space - 7], a + b);
				}
			}

			else if (!strcmp(cmd[now_idx], "서서선")) { // 수 2개 뽑아 곱하고 넣기
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], a * b);
					else // queue라면
						queue_push(q[now_space - 7], a * b);
				}
			}

			else if (!strcmp(cmd[now_idx], "리린")) { // 수 2개 뽑아 빼고 넣기(나중 - 처음)
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], b - a);
					else // queue라면
						queue_push(q[now_space - 7], b - a);
				}
			}

			else if (!strcmp(cmd[now_idx], "리리린")) { // 수 2개 뽑아 나누고 넣기(나중 - 처음)
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else if (!a) {
					error_line = now_idx;
					error = 3;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], b / a);
					else // queue라면
						queue_push(q[now_space - 7], b / a);
				}
			}

			else if (!strcmp(cmd[now_idx], "서선리린")) { // 수 2개 뽑아 나머지 넣기(나중 - 처음)
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else if (!a) {
					error_line = now_idx;
					error = 3;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], b % a);
					else // queue라면
						queue_push(q[now_space - 7], b % a);
				}
			}

			else if (!strcmp(cmd[now_idx], "선")) {
				int nowtop;
				if (now_space < 7)
					nowtop = stack_top(stk[now_space]);
				else
					nowtop = queue_front(q[now_space - 7]);
				if (nowtop == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else if (!nowtop)
					pair_chk = 1;
				else
					stack_push(pair, now_idx);
			}
			else if (!strcmp(cmd[now_idx], "린")) {
				int nowtop;
				if (now_space < 7)
					nowtop = stack_top(stk[now_space]);
				else
					nowtop = queue_front(q[now_space - 7]);
				if (nowtop == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else if (nowtop) {
					now_idx = stack_pop(pair) - 1;
				}
				else
					stack_pop(pair);
			}

			else if (!strcmp(cmd[now_idx], "선 린")){ // 2개 꺼내고 나중이 크면 1, 아니면 0 넣기
				int a, b;
				if (now_space < 7) { // stack이라면
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue라면
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack이라면
						stack_push(stk[now_space], b > a);
					else // queue라면
						queue_push(q[now_space - 7], b > a);
				}
			}

			else if (!strncmp(cmd[now_idx], "선린선", 6)) {
				int tmp_space = count_riin(cmd[now_idx] + 6) % 9;
				int nowtop;
				if (now_space < 7)
					nowtop = stack_top(stk[now_space]);
				else
					nowtop = queue_front(q[now_space - 7]);
				if (tmp_space < 7)
					stack_push(stk[tmp_space], nowtop);
				else
					queue_push(q[tmp_space - 7], nowtop);
			}

			else if (!strncmp(cmd[now_idx], "선", 2)) {
				now_space = count_riin(cmd[now_idx] + 2) % 9;
			}
			else if (!strncmp(cmd[now_idx], "서", 2)) {
				int cnt = count_suun(cmd[now_idx]);
				if (now_space < 7)
					stack_push(stk[now_space], cnt);
				else
					queue_push(q[now_space - 7], cnt);
			}
		}

		free(cmd[0]);
		free(cmd);
	}

	// 에러 처리 해야 함
	if (error) {
		switch (error) {
		case 1:
			fprintf(out, "ERROR 1 : %d번째 줄에서 빈 스택 / 큐의 값을 읽거나 꺼내려 시도했습니다.", error_line + 1);
			break;
		case 3:
			fprintf(out, "ERROR 3 : %d번째 줄에서 0으로 나누는 연산을 시도했습니다.", error_line + 1);
			break;
		}
	}
	fclose(code);
	fclose(out);
	return 0;
}

int count_riin(char* start) {
	int ans = 1;
	bool have_in = false;
	if (!strncmp(start, "린", 2) or strncmp(start, "리", 2))
		return 0;
	for (int i = 2; start[i] != '\0'; i++) {
		if (!strncmp(start + i, "이", 2))
			ans++;
		else if (!strncmp(start + i, "인", 2)) {
			have_in = true;
			break;
		}
	}
	if (have_in)
		return ans;
	else
		return 0;
}
int count_suun(char* start) {
	int ans = 1;
	bool have_un = false;
	if (!strncmp(start, "선", 2) or strncmp(start, "서", 2))
		return 0;
	for (int i = 2; start[i] != '\0'; i++) {
		if (!strncmp(start + i, "어", 2))
			ans++;
		else if (!strncmp(start + i, "언", 2)) {
			have_un = true;
			break;
		}
	}
	if (have_un)
		return ans;
	else
		return 0;
}