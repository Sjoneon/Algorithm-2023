#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dijkstra.h"
#include "menu1.h"
#include "menu3.h"

int nickname_num[10] = { 0 };
int count_num = 1;

void del_BM()
{
    int delete_num = 5;
    delete_num = List_del_BM("Region.txt");

    Delete("Region.txt", R[nickname_num[delete_num-1]].region, delete_num); 

    return 0;
}

int List_del_BM(const char* filename)
{
    int delete_pos = 0;
    load_road_Region(filename);
    count_num = 1;

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(R[i].nickname, " ") == 0)
        {
            // 그냥 넘김
        }
        else
        {
            gotoxy(42, 6 + (2 * count_num));
            printf("%d. %s(%s)\n", count_num, R[i].region, R[i].nickname);
            nickname_num[count_num - 1] = i;
            count_num++;
        }
    }
    gotoxy(42, 19);
    printf("삭제할 즐겨찾기를 선택해주세요 >> ");
    scanf("%d", &delete_pos);

    while (delete_pos == 0 || delete_pos + 1 > count_num)
    {
        gotoxy(42, 19);
        printf("잘못된 입력입니다. 다시 입력해주세요 >> ");

        gotoxy(82, 19);
        printf("       ");
        gotoxy(82, 19);
        scanf("%d", &delete_pos);
    }
    return delete_pos;
}

void Delete(const char* filename, const char* targetArea, int delete_num)
{
    FILE* file = fopen(filename, "r");  // 입력 파일 열기
    FILE* tempFile = fopen("temp.txt", "w");  // 임시 파일 열기

    if (file == NULL || tempFile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // 개행 문자 제거

        char* start = strchr(line, '(');
        if (start != NULL) {
            *start = '\0';  // 지역 문자열 종료

            // 삭제할 지역과 일치하는 경우
            if (strcmp(line, targetArea) == 0) {
                fprintf(tempFile, "%s( )\n", line);  // 별명 유지
                continue;
            }
        }
        fprintf(tempFile, "%s(%s\n", line, start + 1); // 임시 파일에 내용 기록
    }
    fclose(file);
    fclose(tempFile);

    remove(filename);  // 원본 파일 삭제
    rename("temp.txt", filename);  // 임시 파일을 원본 파일 이름으로 변경

    gotoxy(42, 21);
    printf("즐겨찾기 %d번을 삭제하였습니다.\n", delete_num);
    count_num = 1; // 즐겨찾기 번호 초기화
    gotoxy(42, 23);
    printf("please press the enter...");
}

void menu3() 
{
    del_BM();
}
