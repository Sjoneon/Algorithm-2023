#include<stdio.h>
#include <stdlib.h>

int findMax(int arr[], int num)
{
	int Max = arr[0];
	for (int i = 1; i < num; i++)
	{
		if (Max < arr[i])
		{
			Max = arr[i];
		}
	}
	return Max;
}

int main()
{
	int num;
	int arr[100];

	printf("�Է��� ���� : ");
	scanf("%d", &num);

	srand(NULL);

	for (int i = 0; i < num; i++)
	{
		arr[i] = rand();
	}


	int Max = findMax(arr, num);

	printf("�ִ� ���� �� : %d\n", Max);
	return 0;
}
