#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // malloc, free 함수 사용을 위해 필요

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 임시 배열을 동적으로 할당
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 임시 배열에 값을 복사
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 임시 배열 L과 R을 합병하여 arr에 정렬된 값을 저장
    i = 0; // L 배열의 인덱스
    j = 0; // R 배열의 인덱스
    k = left; // arr 배열의 인덱스
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // L 배열에 남은 값이 있다면 arr에 복사
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // R 배열에 남은 값이 있다면 arr에 복사
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // 동적으로 할당한 메모리를 해제
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 왼쪽 부분 배열을 정렬
        merge_sort(arr, left, mid);

        // 오른쪽 부분 배열을 정렬
        merge_sort(arr, mid + 1, right);

        // 두 부분 배열을 합병
        merge(arr, left, mid, right);
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

    merge_sort(arr, 0, n - 1);

    FILE* OutFile = fopen("result.txt", "w");

    if (OutFile == NULL) {
        printf("출력 파일을 열지 못했습니다.\n");
        free(arr);
        return 1;
    }
    else {
        printf("result에 저장되었습니다.\nresult를 확인 해주세요!!!\n");
    }

    fprintf(OutFile, "합병으로 정리한 배열: ");
    for (int i = 0; i < n; i++)
        fprintf(OutFile, "%d ", arr[i]);
    fprintf(OutFile, "\n");

    fclose(OutFile);

    free(arr);

    return 0;
}