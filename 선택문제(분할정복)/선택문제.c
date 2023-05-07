#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b)   // 피봇과 배열의 원소를 교환하는 함수
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partition(int arr[], int left, int right)   // 퀵 정렬을 수행하고 피봇의 인덱스를 반환하는 함수
{
   
    srand(time(NULL));  // 피봇을 랜덤하게 선택

    int pivotindex = left + rand() % (right - left + 1);
    int pivot = arr[pivotindex];

    // 피봇과 A[left]의 위치를 바꿈
    swap(&arr[left], &arr[pivotindex]); 

    int i = left + 1;
    int j = right;

    while (1) 
    {
        while (i <= j && arr[i] < pivot)
            i++;

        while (i <= j && arr[j] > pivot)
            j--;

        if (i > j)
            break;

        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }

    
    swap(&arr[left], &arr[j]);  // 피봇을 알맞은 곳에 위치에 배치

    return j;
}

// Selection 알고리즘
int Selection(int arr[], int left, int right, int k) 
{
    if (left == right)
        return arr[left];

    int pivotIndex = partition(arr, left, right);
    int smallG = pivotIndex - left;

    if (k <= smallG)
        return Selection(arr, left, pivotIndex - 1, k);
    else if (k == smallG + 1)
        return arr[pivotIndex];
    else
        return Selection(arr, pivotIndex + 1, right, k - smallG - 1);
}

int main() 
{
   
    FILE* inFile = fopen("data.txt", "r");  // 파일 읽기

    if (inFile == NULL) 
    {
        printf("Failed to open the input file.\n");
        return 1;
    }

    // 파일에서 정수들을 읽어 배열에 저장

    int maxElements = 1000; // 배열의 최대 크기
    int* arr = malloc(maxElements * sizeof(int));

    if (arr == NULL) 
    {
        printf("Memory allocation failed.\n");
        fclose(inFile);
        return 1;
    }

    int i = 0;

    while (fscanf(inFile, "%d", &arr[i]) != EOF) //EOF는 "End of File"의 약자로, 파일의 끝을 나타내는 상수
    {
        i++;
        if (i >= maxElements)
            break;
    }

    int n = i; // 배열의 실제 크기

    fclose(inFile);

    // Selection 알고리즘 수행
    int k = 5;
    int result = Selection(arr, 0, n - 1, k);

    // 결과 파일에 저장
    FILE* OutFile = fopen("result.txt", "w");

    if (OutFile == NULL)
    {
        printf("Failed to open the output file.\n");
        free(arr);
        return 1;
    }
    else
    {
        printf("result에 저장되었습니다.\nresult를 확인 해주세요!!!\n");
    }

    fprintf(OutFile, "%d번째로 작은 정수: %d\n", k, result);

    fclose(OutFile);

    free(arr);

    return 0;
}