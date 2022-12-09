#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define SIZE 3
typedef struct student {
	int number; // 학번
	char name[20]; // 이름
	double gpa; // 평점
}STUDENT;
int main(void) {
	STUDENT table[SIZE] = {
		{ 1, "Kim", 3.99 },
		{ 2, "Min", 2.68 },
		{ 3, "Lee", 4.01 }
	};
	STUDENT s;
	FILE* fp = NULL;
	int i;
	// 이진 파일을 쓰기 모드로 연다
	if ((fp = fopen("student.txt","wt")) == NULL)
	{
		fprintf(stderr,"출력을 위한 파일을열수 없습니다.\n");
		exit(1);
	}

	// 배열을 파일에 저장한다.
	for (i = 0;i < SIZE; i++) {
		fprintf(fp, "%d\t",table[i].number);
		fprintf(fp, "%s\t", table[i].name);
		fprintf(fp, "%f\n", table[i].gpa);
	}
	fclose(fp);
	// 이진 파일을 읽기 모드로 연다.
	if ((fp = fopen("student.txt", "rt")) == NULL) {
		fprintf(stderr, "입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	for (i = 0;i < SIZE; i++) {
		fscanf(fp,"%d", &s.number);
		fscanf(fp, "%s", &s.name);
		fscanf(fp, "%f", &s.gpa);
		printf("학번 = %d, 이름 = %s, 평점 = %f\n", s.number, s.name, s.gpa);
	}
	fclose(fp);
	return 0;
}