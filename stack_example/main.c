#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S_SIZE 50

typedef struct node {
	char title[S_SIZE];
	int year;
	struct node* link;
} NODE;

typedef struct stack {
	NODE* top;
	int nNodes;
} Stack;

void init(Stack *s) {
	s->top = NULL;
	s->nNodes = 0;
}

int is_empty(Stack* s) {
	return (s->nNodes == 0);
}

void push(Stack* s, char* title, int year) {
	// Data 생성 및 저장
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	strcpy(new_node->title, title);
	new_node->year = year;
	s->nNodes += 1;

	// 생성된 데이터를 스택에 밀어넣기
	if (is_empty(s)) { // 스택이 비어있는 상황
		s->top = new_node;
		new_node->link = NULL;
	}
	else {
		NODE* temp = s->top;
		s->top = new_node;
		new_node->link = temp;
	}
}

void pop(Stack* s) {
	if (is_empty(s)) {
		printf("The stack is empty!\n");
	}
	else {
		NODE* temp = s->top;
		printf("책의 제목:%s, 출판 연도:%d \n", temp->title, temp->year);
		s->top = temp->link;
		s->nNodes -= 1;
		free(temp);
	}
}

void print_stack(Stack *s) {
	NODE* temp = s->top;
	while (temp != NULL) {
		printf("책의 제목:%s, 출판 연도:%d \n", temp->title, temp->year);
		temp = temp->link;
	}
}

int main(void) {
	Stack books;
	init(&books);
	char title[S_SIZE];
	char buffer[S_SIZE];
	int year;
	while (1) {
		printf("책의 제목을 입력하시오: (종료=엔터)");
		gets_s(title, S_SIZE);	// 제목 입력
		if (title[0] == '\0'){	// 엔터인 경우 종료
			break;
		}
		printf("책의 출판 연도를 입력하시오: ");
		gets_s(buffer, S_SIZE);
		year = atoi(buffer);
		
		push(&books, title, year);
	}
	printf("\n");
	//print_stack(&books);

	while(books.top != NULL){
		pop(&books);
	}

	return 0;
}
