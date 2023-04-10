#include<stdio.h>
#include <stdlib.h>
#include <time.h>


void randomboy(int arr[],int num)
{
	srand(time(NULL));

	for (int i = 0; i < num; i++)
	{
		arr[i] = rand();

		printf("랜덤으로 나온 수는 : %d\n", arr[i]); //printf는 원래 함수에 안넣어야되는데 어째 오류가...
	}
}

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

	printf("입력할 개수 : ");
	scanf("%d", &num);


	randomboy(arr,num);

	int Max = findMax(arr, num);

	printf("최대 숫자 값 : %d\n", Max);
	return 0;
}