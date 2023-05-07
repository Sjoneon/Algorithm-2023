#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[], int left, int right) {
    int pivot, i, j, temp;

    // 배열의 크기가 1 이하면 정렬할 필요가 없다
    if (left >= right) {
        return;
    }

    // 피벗을 가운데 원소로 설정한다
    pivot = arr[(left + right) / 2];

    // 피벗을 기준으로 작은 값은 왼쪽으로, 큰 값은 오른쪽으로 옮긴다
    i = left;
    j = right;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            // i와 j의 원소를 교환한다
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    // 분할된 두 부분 배열에 대해 재귀적으로 퀵정렬을 수행한다
    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}

int main() {
    FILE* inFile = fopen("data.txt", "r");

    if (inFile == NULL) {
        printf("입력 파일을 여는데 실패하였습니다.\n");
        return 1;
    }

    int maxElements = 1000;
    int* arr = malloc(maxElements * sizeof(int));

    if (arr == NULL) {
        printf("메모리 할당에 실패하였습니다.\n");
        fclose(inFile);
        return 1;
    }

    int i = 0;

    while (fscanf(inFile, "%d", &arr[i]) != EOF) {
        i++;
        if (i >= maxElements)
            break;
    }

    int n = i;

    fclose(inFile);

    quicksort(arr, 0, n - 1);

    FILE* outFile = fopen("result.txt", "w");

    if (outFile == NULL) {
        printf("출력 파일을 열지 못했습니다.\n");
        free(arr);
        return 1;
    }
    else {
        printf("result에 저장되었습니다.\nresult를 확인해주세요!!!\n");
    }

    fprintf(outFile, "퀵으로 정렬한 배열: ");
    for (int i = 0; i < n; i++)
        fprintf(outFile, "%d ", arr[i]);
    fprintf(outFile, "\n");

    fclose(outFile);

    free(arr);

    return 0;
}