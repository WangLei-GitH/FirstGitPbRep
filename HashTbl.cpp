#include "HashTbl.h"
#include <iostream>

int func(int x)
{
	int countx = 0;
	while (x)
	{
		countx++;
		x = x & (x - 1);
	}
	return countx;
}

int main()
{
// 	double** ppt = new double* [1];
// 	ppt[0] = new double[1];
// 	ppt[0][0] = 2.0;
// 	printf_s("%f", ppt[0][0]);
	int a[3][2] = { 3,2,1 };
	int a1 = a[0][0];
	int a2 = a[0][1];
	int a3 = a[0][2];
	int a4 = a[1][0];
	auto p = a[0][0] / a[0][1] / a[0][2];
	std::cout << func(9999) << std::endl;
}

