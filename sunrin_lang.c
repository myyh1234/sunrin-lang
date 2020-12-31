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
	char tmp[2005], ** cmd; // �� �ٿ� �ִ� 1000���� �� �� ����
	int got_num, pair_chk = 0, now_idx = 0, now_space, error, error_line = 0;
	// -1 : ���� �ڵ尡 ����, 1 : �� ���� / ť�� ������ �õ���, 2 : �� / �� ¦�� ���� ����, 3 : 0���� ����

	FILE* code = fopen("code.txt", "r");
	FILE* out = fopen("output.txt", "w");
	for (int i = 0; i < 7; i++)
		stk[i] = stack_make();

	//------------- �ڵ� Ȯ�� --------------
	while (true) {
		now_idx++;
		error = fgets(tmp, sizeof tmp, code);;
		if (error == NULL) {
			error = -1;
			break;
		}
		error = 0;
		if (!strcmp(tmp, "�� �ڶ� 1�г� 4��!") or !strcmp(tmp, "�� �ڶ� 1�г� 4��!\n"))
			break;
		if (!strcmp(tmp, "��"))
			pair_chk++;
		else if (!strcmp(tmp, "��")) {
			pair_chk--;
			if (pair_chk < 0) {
				error = 2;
				break;
			}
		}
	}
	// ----------- ���� üũ ------------
	if (pair_chk)
		error = 2;
	if (error) {
		if (error == -1)
			fputs("ERROR -1 : ���� �ڵ� \'�� �ڶ� 1�г� 4��!\' �� ã�� �� �����ϴ�.", out);
		else
			fputs("ERROR 2 : \'��\' �� \'��\' �� ¦�� ���� �ʽ��ϴ�.", out);
	}
	else {
		// --------------- ��Ÿ�� --------------

		// ��ɾ� ���� �޸� �Ҵ�
		cmd = malloc(sizeof(char*) * now_idx);
		cmd[0] = malloc(sizeof(char) * 2005 * now_idx);
		for (int i = 1; i < now_idx; i++)
			cmd[i] = cmd[i - 1] + 2005;

		rewind(code); // �ڵ� ó������ �ٽ� ������ command�� ����

		for (int i = 0; i < now_idx; i++) {
			fgets(cmd[i], 2005, code);
			if (cmd[i][strlen(cmd[i]) - 1] == '\n')
				cmd[i][strlen(cmd[i]) - 1] = '\0';
		}

		now_idx = -1;
		now_space = 0;
		pair_chk = 0; // '��'���� top�� 0�� �� �����Ǵ� '��'�� ã�� ���� ���
		while (true) {
			now_idx++;
			if (now_idx == 2)
				now_idx += 0;
			if (now_idx == 67)
				now_idx += 0;
			if (pair_chk) {
				if (!strcmp(cmd[now_idx], "��"))
					pair_chk++;
				else if (!strcmp(cmd[now_idx], "��"))
					pair_chk--;
				continue;
			}

			if (!strcmp(cmd[now_idx], "�� �ڶ� 1�г� 4��!"))
				break;

			if (!strcmp(cmd[now_idx], "����")) { // ���� �Է¹ޱ�
				printf("������ �Է��ϼ��� : ");
				scanf("%d", &got_num);
				if (now_space < 7) // stack�̶��
					stack_push(stk[now_space], got_num);
				else // queue���
					queue_push(q[now_space - 7], got_num);
			}

			else if (!strcmp(cmd[now_idx], "����")) { // ���� ����ϱ�
				int will_print;
				if (now_space < 7) // stack�̶��
					will_print = stack_top(stk[now_space]);
				else // queue���
					will_print = queue_front(q[now_space - 7]);
				if (will_print == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					fprintf(out, "%c", (char)will_print);
			}

			else if (!strcmp(cmd[now_idx], "��������")) { // ���� ����ϱ�
				int will_print;
				if (now_space < 7) // stack�̶��
					will_print = stack_top(stk[now_space]);
				else // queue���
					will_print = queue_front(q[now_space - 7]);
				if (will_print == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					fprintf(out, "%d", will_print);
			}

			else if (!strcmp(cmd[now_idx], "����")) { // �ϳ� �̾� ������
				if (now_space < 7) // stack�̶��
					error = stack_pop(stk[now_space]);
				else // queue���
					error = queue_pop(q[now_space - 7]);
				if (error == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else
					error = 0;
			}

			else if (!strcmp(cmd[now_idx], "����")) { // �� 2�� �̾� ���ϰ� �ֱ�
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], a + b);
					else // queue���
						queue_push(q[now_space - 7], a + b);
				}
			}

			else if (!strcmp(cmd[now_idx], "������")) { // �� 2�� �̾� ���ϰ� �ֱ�
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], a * b);
					else // queue���
						queue_push(q[now_space - 7], a * b);
				}
			}

			else if (!strcmp(cmd[now_idx], "����")) { // �� 2�� �̾� ���� �ֱ�(���� - ó��)
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], b - a);
					else // queue���
						queue_push(q[now_space - 7], b - a);
				}
			}

			else if (!strcmp(cmd[now_idx], "������")) { // �� 2�� �̾� ������ �ֱ�(���� - ó��)
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
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
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], b / a);
					else // queue���
						queue_push(q[now_space - 7], b / a);
				}
			}

			else if (!strcmp(cmd[now_idx], "��������")) { // �� 2�� �̾� ������ �ֱ�(���� - ó��)
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
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
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], b % a);
					else // queue���
						queue_push(q[now_space - 7], b % a);
				}
			}

			else if (!strcmp(cmd[now_idx], "��")) {
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
			else if (!strcmp(cmd[now_idx], "��")) {
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

			else if (!strcmp(cmd[now_idx], "�� ��")){ // 2�� ������ ������ ũ�� 1, �ƴϸ� 0 �ֱ�
				int a, b;
				if (now_space < 7) { // stack�̶��
					a = stack_pop(stk[now_space]);
					b = stack_pop(stk[now_space]);
				}
				else { // queue���
					a = queue_pop(q[now_space - 7]);
					b = queue_pop(q[now_space - 7]);
				}
				if (a == ERROR or b == ERROR) {
					error_line = now_idx;
					error = 1;
					break;
				}
				else {
					if (now_space < 7) // stack�̶��
						stack_push(stk[now_space], b > a);
					else // queue���
						queue_push(q[now_space - 7], b > a);
				}
			}

			else if (!strncmp(cmd[now_idx], "������", 6)) {
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

			else if (!strncmp(cmd[now_idx], "��", 2)) {
				now_space = count_riin(cmd[now_idx] + 2) % 9;
			}
			else if (!strncmp(cmd[now_idx], "��", 2)) {
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

	// ���� ó�� �ؾ� ��
	if (error) {
		switch (error) {
		case 1:
			fprintf(out, "ERROR 1 : %d��° �ٿ��� �� ���� / ť�� ���� �аų� ������ �õ��߽��ϴ�.", error_line + 1);
			break;
		case 3:
			fprintf(out, "ERROR 3 : %d��° �ٿ��� 0���� ������ ������ �õ��߽��ϴ�.", error_line + 1);
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
	if (!strncmp(start, "��", 2) or strncmp(start, "��", 2))
		return 0;
	for (int i = 2; start[i] != '\0'; i++) {
		if (!strncmp(start + i, "��", 2))
			ans++;
		else if (!strncmp(start + i, "��", 2)) {
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
	if (!strncmp(start, "��", 2) or strncmp(start, "��", 2))
		return 0;
	for (int i = 2; start[i] != '\0'; i++) {
		if (!strncmp(start + i, "��", 2))
			ans++;
		else if (!strncmp(start + i, "��", 2)) {
			have_un = true;
			break;
		}
	}
	if (have_un)
		return ans;
	else
		return 0;
}