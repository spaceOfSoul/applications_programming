#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define SCALE 3

int MAX(int* price, int dim) {
	int result = 0;
	for (int i = 0; i < dim; i++) {
		if (price[i] > result) {
			result = price[i];
		}
	}
	return result;
}

int count(FILE *fp) {
	int result = 0;
	char buff[100];
	while (feof(fp) == 0) {
		fscanf(fp, "%s\n", buff, 1);
		//printf("%s\n", buff);
		result++;
	}
	result--;
	return result;
}

void readPrice(FILE *fp, int *price, int dim) {
	char buff[100];
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%s\n", buff, 1);	// Date, Open, High, .....
	char* token;
	int idx = 0;
	while (feof(fp) == 0) {
		fscanf(fp, "%s\n", buff, 1); // 2020-9-18, 37200.0, ....
		token = strtok(buff, ",");
		token = strtok(NULL, ",");
		//printf("%s\n", token);
		// 
		price[dim-idx-1] = atoi(token);
		idx++;
	}
}


int main(void) {
	FILE* fp = fopen("./000080.txt", "rt");
	if (fp == NULL) {
		printf("failed to open file\n");
		return 0;
	}

	int nLeng = count(fp);
	printf("the number of lines: %d\n", nLeng);

	int* price = (int*)malloc(nLeng * sizeof(int));
	readPrice(fp, price,nLeng);

	// �׸� �׸���
	HWND hwnd = GetForegroundWindow();
	HDC  hdc = GetWindowDC(hwnd);
	int max_price = MAX(price, nLeng);
	int x, y;

	MoveToEx(hdc, 30, 400, 0);
	LineTo(hdc, 30, 0);
	MoveToEx(hdc, 30, 400, 0);
	LineTo(hdc, 30 + SCALE * nLeng, 400);

	x = SCALE * 0 + 30;
	y = 400 - (int)150 * ((float)price[0] / (float)max_price);
	//SetPixel(hdc, x, y, RGB(255, 0, 0));
	MoveToEx(hdc, x,y, 0);
	//http://soen.kr/lecture/win32api/lec4/lec4-3-2.htm
	for (int i = 1; i < nLeng; i++) {
		x = SCALE * i + 30;
		y = 400 - (int)150 * ((float)price[i] / (float)max_price);
		
		//SetPixel(hdc, x, y, RGB(255, 0, 0));
		LineTo(hdc,x,y);
	}


	free(price);
	fclose(fp);
	return 0;
}