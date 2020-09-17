//#include <iostream>
#include <stdio.h>
#include <cmath>

int main()
{
    /*while (true)
    {
        int N, i = 0;
        printf("Enter number N:\n");
        scanf_s("%d", &N);
        int flag = 0;
        for (i = 2; i < N; i++)
        {
            if (N % i == 0)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("True\n\n");
        }
        else
        {
            printf("False\n\n");
        }

    }*/

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
}