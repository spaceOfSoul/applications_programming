#include <windows.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14
#define X0 30
#define Y0 300

double sinwave(int degree, int scale) {
	double result = 0;
	return result = scale * sin(PI * degree / 180);
}

// GetForegroundWindow()
// GetWindowDC()
// SetPixel()

int main(void) {
	HWND hwnd = GetForegroundWindow(); // 프로그램들 상에서 가장 앞에 있는 창
	HDC hdc = GetWindowDC(hwnd); // hwnd의 권한얻기
	double result=0; 
	int x, y;

	//sine wave
	for (int deg = 0;deg < 360;deg++) {
		result = sinwave(deg, 100);
		x = X0 + deg;
		y = Y0 + (int)result;
		SetPixel(hdc, x, y, RGB(0, 255, 0));
	}
	/*
	* for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			SetPixel(hdc, 300+i, 300+j, RGB(0, 255, 0));
		}
	}
	*/
}