#include <iostream>
#include <cmath>
using namespace std;

int getNumCount (int N)
{
	int M = N;
	int l = 0;
	while (M != 0)
	{
		M = M / 10;
		l += 1;
	}
	return l;
}

int getNumSum(int N)
{
	int l = getNumCount(N);
	int M = N, S = 0;
	for (int i = l; i != 0; i--)
	{
		M = N / (int)pow(10, i - 1);
		M = M % 10;
		S += M;
	}
	return S;
}

double vzrivMozga(double N)
{
	if n = 1
	{
		return 1;
	}
	else
	{
		return (vzrivMozga(N-1) + (2 / vzrivMozga(N - 1))) / 2;
	}
}

int main()
{
/*
	int N;
	cout << "Enter number N:\n";
	cin >> N;
	while (N % 17 != 0)
	{
		N += 1;
	}
	cout << N;
*/
/*
	while (true)
	{
		int M, N, l = 0, c = 0, No = 0, j = 0;
		printf("Enter number:\t");
		scanf_s("%d", &N);
		M = N;
		while (M != 0)
		{
			M = M / 10;
			l += 1;
		}
		printf("l = %d\n", l);
		for (int i = 0; i < l; i++)
		{
			c = N / (int)pow(10, i);
			c = c % 10;
			if (c != 1)
			{
				No += c * pow(10, i - j);
			}
			else
			{
				j++;
			}
		}
		if (j != l)
		{
			printf("%d\n", No);
		}
		printf("\n");
	}
*/
/*
	int N, O=0;
	while (true)
	{
		cout << "\nEnter number N:\n";
		cin >> N;
		int S = getNumSum(N);
		cout << "NSum = " << S << "\n";
		for (int M = N + 1; M < 2 * N && M % S != 0; M++)
		{
			O = M + 1;
		}
		if (O % S == 0)
		{
			cout << "Number: " << O << "\n";
		}
		else
		{
			cout << "No.";
		}
	}
*/

	double N, e;
	cout << "Enter number N:\n";
	cin >> N;
	cout << "Enter number e:\n";
	cin >> e;
	for (double a = 1; abs(pow(vzrivMozga(a),2) - 2) >= e || a < N; a++)

}
