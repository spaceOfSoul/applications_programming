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

typedef struct queue {
    NODE* front;
    NODE* rear;
    int nNodes;
} Queue;


void init(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->nNodes = 0;
}



int is_empty(Queue* q) {
    return (q->nNodes == 0);
}

void enqueue(Queue* q, char* title, int year) {
    // 노드 생성
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    strcpy(new_node->title, title);
    new_node->year  = year;
    new_node->link = NULL;
    
    // 큐에 저장
    if (is_empty(q)) {
        q->front = new_node;
        q->rear = new_node;
    }else {
        q->rear->link = new_node;
        q->rear = new_node;
    }
    q->nNodes += 1;
}



void dequeue(Queue* q){
    if (is_empty(q)) {
        printf("Warning: Queue is empty!\n");
    }
    else {
        NODE* temp = q->front;
        printf("[dequeue] 책의 제목:%s, 출판 연도:%d \n", temp->title, temp->year);
        q->front = temp->link;
        if (q->nNodes == 1) {
            q->rear = NULL;
        }
        free(temp);
        q->nNodes -= 1;
    }
}



void print_queue(Queue* q) {
    NODE* temp = q->front;
    while (temp != NULL) {
        printf("[print] 책의 제목:%s, 출판 연도:%d \n", temp->title, temp->year);
        temp = temp->link;
    }
}

int main(void) {
    Queue books;
    init(&books);
    char title[S_SIZE];
    char buffer[S_SIZE];
    int year;

    printf("# of nodes in Queue: %d\n", books.nNodes);
    printf("is this Queue empty? %d (1=yes, 0=no)", is_empty(&books));
    
    while (1) {
        printf("책의 제목을 입력하시오: (종료=엔터)");
        gets_s(title, S_SIZE);// 제목 입력
        if (title[0] == '\0'){// 엔터인 경우 종료
            break;
        }
        printf("책의 출판 연도를 입력하시오: ");
        gets_s(buffer, S_SIZE);
        year = atoi(buffer);
        enqueue(&books, title, year);
    }
    printf("\n");
    printf("is this Queue empty? %d (1=yes, 0=no)", is_empty(&books));

    print_queue(&books);

    printf("# of nodes in Queue: %d\n", books.nNodes);
    printf("is this Queue empty? %d (1=yes, 0=no)", is_empty(&books));

    while(books.front != NULL){
        dequeue(&books);
    }
    printf("# of nodes in Queue: %d\n", books.nNodes);
    printf("is this Queue empty? %d (1=yes, 0=no)", is_empty(&books));
    return 0;
}