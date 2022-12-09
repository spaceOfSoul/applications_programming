#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define SIZE 3
typedef struct student {
	int number; // �й�
	char name[20]; // �̸�
	double gpa; // ����
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
	// ���� ������ ���� ���� ����
	if ((fp = fopen("student.txt","wt")) == NULL)
	{
		fprintf(stderr,"����� ���� ���������� �����ϴ�.\n");
		exit(1);
	}

	// �迭�� ���Ͽ� �����Ѵ�.
	for (i = 0;i < SIZE; i++) {
		fprintf(fp, "%d\t",table[i].number);
		fprintf(fp, "%s\t", table[i].name);
		fprintf(fp, "%f\n", table[i].gpa);
	}
	fclose(fp);
	// ���� ������ �б� ���� ����.
	if ((fp = fopen("student.txt", "rt")) == NULL) {
		fprintf(stderr, "�Է��� ���� ������ �� �� �����ϴ�.\n");
		exit(1);
	}
	for (i = 0;i < SIZE; i++) {
		fscanf(fp,"%d", &s.number);
		fscanf(fp, "%s", &s.name);
		fscanf(fp, "%f", &s.gpa);
		printf("�й� = %d, �̸� = %s, ���� = %f\n", s.number, s.name, s.gpa);
	}
	fclose(fp);
	return 0;
}