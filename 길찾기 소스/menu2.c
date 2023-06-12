#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dijkstra.h"
#include "menu.h"
#include "menu1.h"
#include "menu2.h"

#define _CRT_SECURE_NO_WARNINGS

void add_BM() // 별명 추가함수
{
    List_add_BM("Region.txt");
    Register("Region.txt");
}

void List_add_BM(const char* filename) // 별명(지역)파일(리스트)열기 함수
{
    load_road_Region(filename);
}


int check_region(const char* filename, const char* region)  // 지역 여부 확인 함수
{
    FILE* file = fopen(filename, "r");  // 입력 파일 열기

    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 0;
    }

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // 개행 문자 제거

        char* start = strchr(line, '(');
        if (start != NULL) {
            *start = '\0';  // 지역 문자열 종료

            // 기존에 해당 지역이 있는 줄을 찾음
            if (strcmp(line, region) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

void Register(const char* filename) // 지역 등록 함수
{
    char region[50];
    char nickname[50];

    gotoxy(42, 17);
    printf("추가할 지역을 입력하세요: ");
    scanf("%s", region);

    

    while (1)
    {
        int found = check_region(filename, region);
        if (!found) {
            
            gotoxy(42, 17);
            printf("                               ");

            gotoxy(72, 18);
            printf("           ");

            gotoxy(47, 17);
            printf("해당 지역은 존재하지 않습니다.");
            gotoxy(49, 18);
            printf("다시 입력해주십시오 >> ", region);
            scanf("%s", region);
        }
        else
        {
            gotoxy(42, 20);
            printf("추가할 별명을 입력하세요: ");
            scanf("%s", nickname);

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

                    // 기존에 해당 지역이 있는 줄을 찾아 별명을 덮어씌움
                    if (strcmp(line, region) == 0) {
                        fprintf(tempFile, "%s(%s)\n", region, nickname); // 새로운 지역과 별명으로 덮어쓰기
                    }
                    else {
                        fprintf(tempFile, "%s(%s\n", line, start + 1); // 임시 파일에 내용 기록
                    }
                }
                else {
                    fprintf(tempFile, "%s\n", line); // 임시 파일에 내용 기록
                }
            }

            fclose(file);
            fclose(tempFile);

            remove(filename);  // 원본 파일 삭제
            rename("temp.txt", filename);  // 임시 파일을 원본 파일 이름으로 변경

            gotoxy(42, 22);
            printf("별명이 추가되었습니다.\n");
            gotoxy(42, 24);
            printf("please press the enter...");
            break;
        }
    }
}

void menu2() // 최종 메뉴 2번 함수
{
    add_BM();
}
