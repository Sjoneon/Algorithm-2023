#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

#define MAX 16
typedef struct Point {
    int x, y; // (x, y)좌표
    int idx; // 최소값이 나왔을 때 저장하는 변수
} Point;

Point points[MAX];
int min_a, min_b;
double min_dist = -1; // 초기상태

// 두 점 사이의 거리를 계산하는 함수
double distance(Point a, Point b) {
    int dx = a.x - b.x;     // 두 점의 x 좌표 차이를 계산하여 dx에 저장합니다.
    int dy = a.y - b.y;     // 두 점의 y 좌표 차이를 계산하여 dy에 저장합니다.
    return sqrt(dx * dx + dy * dy);     // 두 점 사이의 거리를 계산하여 반환합니다.
                                        //왼쪽 위 (피타고라스의 정리)
}

// 가장 가까운 쌍을 찾는 함수
void find_closest_pair() {
    for (int i = 0; i < MAX; i++) {
        for (int j = i + 1; j < MAX; j++) {

            // 두 점 사이의 거리 계산
            double dist = distance(points[i], points[j]); // (0,1), (0,2), (0,3) 이런식으로 순차적으로 비교함

            // 최소거리가 초기상태인 경우 또는 현재 거리가 최소거리보다 작은 경우
            if (min_dist == -1 || dist < min_dist) // 최소거리가 -1이거나 (초기상태) dist가 최소거리보다 작을경우
            {
                min_dist = dist;        // 최소거리를 갱신
                points[i].idx = i;      // 최소거리를 가지는 점들의 인덱스를 저장
                points[j].idx = j;
                min_a = points[i].idx;  // 가장 가까운 점 쌍의 인덱스를 저장
                min_b = points[j].idx; // 즉 min_a와 min_b의 두 좌표를 두 변수에 저장
            }
        }
    }
} // 단점 : 시간복잡도가 n!이라서 수가 많아질수록 최악으로 가는 코드이다.

int main()
{

    FILE* fp = NULL;        // 파일 포인터 변수 선언 (입력 파일용)
    FILE* fp1 = NULL;       // 파일 포인터 변수 선언 (출력 파일용)

    int a, b;               // 임시 변수 선언
    int i = 0;              // 반복문 인덱스 변수 초기화

    fp = fopen("data.txt", "r");        // "data.txt" 파일을 읽기 모드로 열기
    fp1 = fopen("result.txt", "w");     // "result.txt" 파일을 쓰기 모드로 열기
    if (fp == NULL)
    {
        printf("파일 열기 실패\n");   // 파일 열기에 실패한 경우 오류 메시지 출력
        return 1; //실패를 출력하고 종료
    }
    else
    {
        printf("파일 열기 성공\n");
    }


    // 파일에서 정수를 읽어오면서 배열에 저장하는 과정
    while (fscanf(fp, "%d %d\n", &a, &b) != EOF) {

        points[i].x = a; // 값을 x값에 저장
        points[i].y = b; // 값을 y값에 저장
        printf("[%d %d]\n", points[i].x, points[i].y); // 읽어온 데이터 출력
        i++; // 배열 위치 한 칸 이동
    }


    find_closest_pair();        // 가장 가까운 쌍을 찾는 함수 호출


    // 결과를 파일에 쓰기
    fprintf(fp1, "최근접 쌍의 점 : (%d %d) and (%d %d)",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y); // 파일에 정수 쓰기


    // 결과 출력
    printf("최근접 쌍의 점: (%d, %d) and (%d, %d)\n",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y);
    printf("최소 거리 : %.2lf\n", min_dist);


    fclose(fp);
    fclose(fp1);
    printf("\n");
    return 0;
}
