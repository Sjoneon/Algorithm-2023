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

double distance(Point a, Point b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void find_closest_pair() {
    for (int i = 0; i < MAX; i++) {
        for (int j = i + 1; j < MAX; j++) {
            double dist = distance(points[i], points[j]); // (0,1), (0,2), (0,3) 이런식으로 순차적으로 비교함
            if (min_dist == -1 || dist < min_dist) // 최소거리가 -1이거나 (초기상태) dist가 최소거리보다 작을경우
            {
                min_dist = dist;
                points[i].idx = i;
                points[j].idx = j;
                min_a = points[i].idx;
                min_b = points[j].idx; // 두 좌표를 두 변수에 저장
            }
        }
    }
} // 단점 : 시간복잡도가 n!이라서 수가 많아질수록 최악으로 가는 코드이다.

int main()
{

    FILE* fp = NULL;
    FILE* fp1 = NULL;

    int a, b;
    int i = 0;

    fp = fopen("data.txt", "r");
    fp1 = fopen("result.txt", "w");
    if (fp == NULL)
    {
        printf("파일 열기 실패\n");
        return 1;
    }
    else
    {
        printf("파일 열기 성공\n");
    }


    while (fscanf(fp, "%d %d\n", &a, &b) != EOF) { // 파일에서 정수 읽어오기

        points[i].x = a; // 값을 x값에 저장
        points[i].y = b; // 값을 y값에 저장
        printf("[%d %d]\n", points[i].x, points[i].y); // 읽어온 데이터 출력
        i++; // 배열위치 한칸 이동
    }


    find_closest_pair();


    fprintf(fp1, "최근접 쌍의 점 : (%d %d) and (%d %d)",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y); // 파일에 정수 쓰기


    printf("최근접 쌍의 점: (%d, %d) and (%d, %d)\n",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y);
    printf("최소 거리 : %.2lf\n", min_dist);


    fclose(fp);
    fclose(fp1);
    printf("\n");
    return 0;
}