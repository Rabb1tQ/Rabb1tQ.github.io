#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
//lesser.c -- �ҳ����������н�С��һ��
int imin(int, int);
int main(void)
{
 int answer;
 int evil1, evil2;
 //printf("Enter a pair of integers (q to quit):\n");
 //while (scanf("%d %d", &evil1, &evil2) == 2)
 //{
  //printf("The lesser of %d and %d is %d.\n",evil1, evil2, imin(evil1, evil2));
  //printf("Enter a pair of integers (q to quit):\n");
 answer = 2 * imin(scanf("%d\n", &evil1), scanf("%d\n", &evil2)) + 25;
 //printf("%d\n", answer);
 printf("%d\n", imin(-32 + answer,answer));
  
 //}
 //printf("Bye.\n");
 return 0;
}
int imin(int n, int m)
{
 int min;
 if (n < m)
  min = n;
 else
  min = m;
 return min;
}
