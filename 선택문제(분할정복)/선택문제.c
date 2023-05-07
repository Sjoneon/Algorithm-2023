#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int* a, int* b)   // 피봇과 배열의 원소를 교환하는 함수
{
    int temp = *a;  // 임시 변수 temp에 a가 가리키는 값 저장
    *a = *b;        // a가 가리키는 곳에 b가 가리키는 값 대입
    *b = temp;      // b가 가리키는 곳에 temp에 저장된 값 대입
}


int partition(int arr[], int left, int right)   // 퀵 정렬을 수행하고 피봇의 인덱스를 반환하는 함수
{
   
    srand(time(NULL));  // 피봇을 랜덤하게 선택하기 위한 난수 초기화

    int pivotindex = left + rand() % (right - left + 1);    // 피봇의 인덱스를 랜덤하게 선택
    int pivot = arr[pivotindex];                            // 선택된 피봇의 값

    // 피봇과 A[left]의 위치를 바꿈
    swap(&arr[left], &arr[pivotindex]);                     // 피봇과 배열의 맨 왼쪽 원소를 교환

    int i = left + 1;           // 왼쪽에서 오른쪽으로 진행하는 인덱스
    int j = right;              // 오른쪽에서 왼쪽으로 진행하는 인덱스

    while (1) 
    {
        while (i <= j && arr[i] < pivot)        // 피봇보다 작은 값을 찾을 때까지 i를 증가
            i++;

        while (i <= j && arr[j] > pivot)        // 피봇보다 큰 값을 찾을 때까지 j를 감소
            j--;

        if (i > j)                              // i와 j가 엇갈리면 반복문 종료
            break;

        swap(&arr[i], &arr[j]);                 // i와 j 위치에 있는 원소 교환
        i++;
        j--;
    }

    
    swap(&arr[left], &arr[j]);                  // 피봇을 알맞은 곳에 위치에 배치

    return j;           // 피봇의 최종 위치 반환
}

// Selection 알고리즘
int Selection(int arr[], int left, int right, int k) 
{
    if (left == right)      // 배열의 크기가 1인 경우 해당 원소를 반환
        return arr[left];

    int pivotIndex = partition(arr, left, right);       // 배열을 분할하고 피봇의 인덱스를 얻음
    int smallG = pivotIndex - left;                     // 피봇을 기준으로 왼쪽에 있는 작은 값의 개수

    if (k <= smallG)            // k가 작은 값의 개수보다 작거나 같은 경우
        return Selection(arr, left, pivotIndex - 1, k);         // 왼쪽 부분 배열에서 k번째 작은 값을 찾음
    else if (k == smallG + 1)           // k가 작은 값의 개수 + 1과 같은 경우
        return arr[pivotIndex];         // 피봇 값이 k번째 작은 값임
    else
        return Selection(arr, pivotIndex + 1, right, k - smallG - 1);   // 오른쪽 부분 배열에서 (k - 작은 값의 개수 - 1)번째 작은 값을 찾음 
}

int main() 
{
   
    FILE* inFile = fopen("data.txt", "r");  // 파일 읽기

    if (inFile == NULL) 
    {
        printf("입력 파일을 여는데 실패하였습니다.\n");
        return 1;
    }

    // 파일에서 정수들을 읽어 배열에 저장

    int maxElements = 1000; // 배열의 최대 크기
    int* arr = malloc(maxElements * sizeof(int));   // 동적으로 배열 할당

    if (arr == NULL) 
    {
        printf("메모리 할당에 실패하였습니다.\n");
        fclose(inFile);
        return 1;
    }

    int i = 0;

    while (fscanf(inFile, "%d", &arr[i]) != EOF) //EOF는 "End of File"의 약자로, 파일의 끝을 나타내는 상수
    {                                            //왼쪽 추가 설명 : 파일에서 정수들을 읽어 배열에 저장
        i++;
        if (i >= maxElements)
            break;
    }

    int n = i; // 배열의 실제 크기

    fclose(inFile);     // 입력 파일 닫기

    // Selection 알고리즘 수행
    int k = 5;
    int result = Selection(arr, 0, n - 1, k);       // Selection 알고리즘을 통해 k번째 작은 값을 찾음

    
    FILE* OutFile = fopen("result.txt", "w");   // 결과 파일에 열기

    if (OutFile == NULL)
    {
        printf("출력 파일을 열지 못했습니다.\n");
        free(arr);
        return 1;
    }
    else
    {
        printf("result에 저장되었습니다.\nresult를 확인 해주세요!!!\n");
    }

    fprintf(OutFile, "%d번째로 작은 정수: %d\n", k, result);       // 결과를 파일에 저장

    fclose(OutFile);    // 출력 파일 닫기

    free(arr);      // 동적으로 할당한 배열 메모리 해제

    return 0;
}
