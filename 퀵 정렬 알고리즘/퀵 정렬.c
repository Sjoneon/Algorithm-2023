#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[], int left, int right)
{
    int pivot, i, j, temp;

    // 배열의 크기가 1 이하면 정렬할 필요가 없다
    if (left >= right)
    {
        return;
    }

    // 피벗을 가운데 원소로 설정한다
    pivot = arr[(left + right) / 2];

    // 피벗을 기준으로 작은 값은 왼쪽으로, 큰 값은 오른쪽으로 옮긴다
    i = left;
    j = right;
    while (i <= j)
    {
        while (arr[i] < pivot) //arr[i] < pivot인 동안 i를 증가시키면서 pivot보다 작은 원소를 찾는다.
        {
            i++;
        }
        while (arr[j] > pivot) //arr[j] > pivot인 동안 j를 감소시키면서 pivot보다 큰 원소를 찾는다.
        {
            j--;
        }
        if (i <= j) //i와 j가 만나지 않은 경우
        {
            // i와 j의 원소를 교환한다
            temp = arr[i];      //i와 j의 원소를 교환하고 i를 증가시키고, j를 감소시킵니다.
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }       //pivot을 중심으로 작은 값은 i의 왼쪽으로, 큰 값은 j의 오른쪽으로 분할할 수 있다.
    }

    // 분할된 두 부분 배열에 대해 재귀적으로 퀵정렬을 수행한다
    if (left < j)
    {
        quicksort(arr, left, j);
    }
    if (i < right)
    {
        quicksort(arr, i, right);
    }
}

/*
arr: 동적으로 할당된 정수 배열을 가리키는 포인터 변수입니다.
i: 배열에 저장된 정수의 개수를 세기 위한 변수입니다.
n: 배열의 실제 크기를 저장하는 변수입니다.
*/

int main()
{
    FILE* inFile = fopen("data.txt", "r");      // 입력 파일을 열기

    if (inFile == NULL)
    {
        printf("입력 파일을 여는데 실패하였습니다.\n");
        return 1;
    }

    int maxElements = 1000;
    int* arr = malloc(maxElements * sizeof(int));       // 정수 배열을 동적으로 할당

    if (arr == NULL)
    {
        printf("메모리 할당에 실패하였습니다.\n");
        fclose(inFile);
        return 1;
    }

    int i = 0;      // 정수 배열의 인덱스 변수

    while (fscanf(inFile, "%d", &arr[i]) != EOF)    // 파일에서 정수들을 읽어 배열에 저장
    {
        i++;
        if (i >= maxElements)
            break;
    }

    int n = i;      // 배열의 실제 크기

    fclose(inFile);     // 입력 파일 닫기

    quicksort(arr, 0, n - 1);   // 퀵 정렬 수행

    FILE* outFile = fopen("result.txt", "w");   // 결과 파일을 열기

    if (outFile == NULL)
    {
        printf("출력 파일을 열지 못했습니다.\n");
        free(arr);
        return 1;
    }
    else
    {
        printf("result에 저장되었습니다.\nresult를 확인해주세요!!!\n");
    }

    fprintf(outFile, "퀵으로 정렬한 배열: ");   // 정렬된 배열을 결과 파일에 저장
    for (int i = 0; i < n; i++)
        fprintf(outFile, "%d ", arr[i]);
    fprintf(outFile, "\n");

    fclose(outFile);        // 출력 파일 닫기

    free(arr);      // 동적으로 할당한 메모리 해제

    return 0;
}
