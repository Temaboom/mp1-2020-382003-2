#include "locale.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double LogN(double x, double eps, int *iterat) 
{
	double lastresult, result;
	int n = 0;
	lastresult = 0;
	do 
	{
		result = lastresult;
		lastresult += (pow(-1, n) * pow(x, n + 1)) / (n + 1);
		n++;
		if (n >= (*iterat)) { printf("\n���������"); break; }
	} 
	while (fabs(lastresult - result) >= eps);

	if (n <= (*iterat)) (*iterat) = n;
	else (*iterat) -= n;
	return lastresult;
}

double InputOptions(double *x, int *iter, double *eps) {
	printf("\n������� �������� ��������� ");
	scanf_s("%lf", x);
	printf("\n������� ������������ ���������� ��������� ");
	scanf_s("%d", iter);
	printf("\n������� ����������� \n");
	scanf_s("%lf", eps);
}

double Clear(double *rr, double *x, double *eps, int *itr) 
{
	(*rr) = 0;
	(*x) = 0;
	(*eps) = 0;
	(*itr) = 0;
}

double CosX(double x, double eps, int* count)
{
	double sum = 0;
	double z = 1;
	int n = 0;
	while (fabs(z) > eps)
	{
		sum += z;
		if (n >= (*count))
			break;
		n++;
		z *= -x * x / (2.0 * n - 1.0) / (2.0 * n);
	}
	if ((n != 1) && (n <= (*count)))
		(*count) = n;
	else
		(*count) -= (n);
	if (n == 1)
		(*count) = n;

	return sum;
}

void menu()
{
	printf("\n���������� �� �������:\n");
	printf("1) Ln(1+x) \n");
	printf("2) Sec(x)\n");
	printf("0) �����\n");
}

void main()
{
	setlocale(LC_CTYPE, "Russian");
	printf("��������� �� ���������� ������� ����� ��� �������\n");
	int t = 10;
	double x;   /* �������� ������� */
	double result = 0;      /* ��������� ���������� ������� */
	double eps; /* �������� */
	int iter;   /* �������� -- ���������� ��������� */

	while (t != 0)
	{
		menu();
		scanf_s("%d", &t);
		switch (t)
		{
		case 1:
		{
			printf("\n������ Ln(1+x)");
			printf("\n�������� -1<X<=1:");
			InputOptions(&x, &iter, &eps);
			result = LogN(x, eps, &iter);
			printf("��� ��������� = %16.13f \n���-�� ������ = %5d\nln(x + 1) = %16.13f\n", result, iter, log(x + 1));
			printf("\n������� ����� ������� � ��������� ���������: %16.30f", (log(x + 1) - result));
			Clear(&result, &x, &eps, &iter);
			break;
		}
		case 2:
		{
			printf("������ Sec x");
			InputOptions(&x, &iter, &eps);

			result = CosX(x, eps, &iter);
			printf("��� ��������� = %16.13f \n���-�� ������ = %5d\nSec(x) = %16.13f\n", 1/result, iter, 1/cos(x));
			printf("\n������� ����� ������� � ��������� ���������: %16.30f", 1/result - 1/cos(x));
			Clear(&result, &x, &eps, &iter);
			break; 
		}
		}
	}
}