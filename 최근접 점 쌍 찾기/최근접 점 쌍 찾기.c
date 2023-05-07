#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

#define MAX 16
typedef struct Point {
    int x, y; // (x, y)��ǥ
    int idx; // �ּҰ��� ������ �� �����ϴ� ����
} Point;

Point points[MAX];
int min_a, min_b;
double min_dist = -1; // �ʱ����

double distance(Point a, Point b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void find_closest_pair() {
    for (int i = 0; i < MAX; i++) {
        for (int j = i + 1; j < MAX; j++) {
            double dist = distance(points[i], points[j]); // (0,1), (0,2), (0,3) �̷������� ���������� ����
            if (min_dist == -1 || dist < min_dist) // �ּҰŸ��� -1�̰ų� (�ʱ����) dist�� �ּҰŸ����� �������
            {
                min_dist = dist;
                points[i].idx = i;
                points[j].idx = j;
                min_a = points[i].idx;
                min_b = points[j].idx; // �� ��ǥ�� �� ������ ����
            }
        }
    }
} // ���� : �ð����⵵�� n!�̶� ���� ���������� �־����� ���� �ڵ��̴�.

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
        printf("���� ���� ����\n");
        return 1;
    }
    else
    {
        printf("���� ���� ����\n");
    }


    while (fscanf(fp, "%d %d\n", &a, &b) != EOF) { // ���Ͽ��� ���� �о����

        points[i].x = a; // ���� x���� ����
        points[i].y = b; // ���� y���� ����
        printf("[%d %d]\n", points[i].x, points[i].y); // �о�� ������ ���
        i++; // �迭��ġ ��ĭ �̵�
    }


    find_closest_pair();


    fprintf(fp1, "�ֱ��� ���� �� : (%d %d) and (%d %d)",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y); // ���Ͽ� ���� ����


    printf("�ֱ��� ���� ��: (%d, %d) and (%d, %d)\n",
        points[min_a].x, points[min_a].y, points[min_b].x, points[min_b].y);
    printf("�ּ� �Ÿ� : %.2lf\n", min_dist);


    fclose(fp);
    fclose(fp1);
    printf("\n");
    return 0;
}