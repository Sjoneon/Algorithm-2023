#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"
#include "menu.h"

char save = 72;
int selectedOption = 1;  // 선택된 옵션을 저장할 변수, 기본값으로 1 설정

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void point(int x, int y) {
    char key = 72;
    while (key != 13) {
        key = _getch();
        if (key == 72 || key == 80) {
            gotoxy(x, y + (selectedOption - 1) * 2);
            printf(" ");  // 이전 선택된 옵션의 화살표 삭제

            if (key == 72) {  // 위쪽 화살표 키
                selectedOption = (selectedOption - 1 <= 0) ? 5 : selectedOption - 1;
            }
            else if (key == 80) {  // 아래쪽 화살표 키
                selectedOption = (selectedOption + 1 > 5) ? 1 : selectedOption + 1;
            }

            gotoxy(x, y + (selectedOption - 1) * 2);
            printf("▶");  // 새로 선택된 옵션에 화살표 표시
        }
    }
}

void s(void) //네모난 박스
{
    printf("                               ┌");
    for (int i = 0; i < 58; i++) {  // 1 오른쪽 너비 여기로 줄임
        printf("─");
    }
    printf("┐");
    for (int i = 2; i <= 28; i++) {
        gotoxy(91, i);// 2 오른쪽 너비 여기로 줄임
        printf("│");
    }
    gotoxy(91, 29);// 3 오른쪽 너비 여기로 줄임
    printf("┘");
    for (int i = 60; i > 2; i--) {// 4, 60저거 오른쪽 너비 여기로 줄임
        gotoxy(i + 30, 29);
        printf("─");
    }
    gotoxy(32, 29);
    printf("└");
    for (int i = 28; i > 1; i--) {
        gotoxy(32, i);
        printf("│");
    }
}

void printMenu(int x, int y) {
    gotoxy(x, y);
    printf("    1. 길 찾기");
    gotoxy(x, y + 2);
    printf("    2. 즐겨찾기 추가");
    gotoxy(x, y + 4);
    printf("    3. 즐겨찾기 삭제");
    gotoxy(x, y + 6);
    printf("    4. 최근 기록");
    gotoxy(x, y + 8);
    printf("    5. 종료");
    gotoxy(x, y + 10);
    printf("========================================");
}

void sub1page()
{
    s();
    gotoxy(42, 5);
    printf("========================================");
    //gotoxy(42, 6);
    //printf("         여기다가 출발지 넣고           ");
   // gotoxy(42, 7);
   // printf("         여기다가 도착지 넣고           ");
   /*
    gotoxy(42, 8);
    printf("========================================");
    gotoxy(42, 9);
    printf("              이용 수단                 ");
    gotoxy(42, 10);
    printf("               1. 도보                  ");
    gotoxy(42, 11);
    printf("               2. 자동차                ");
    gotoxy(42, 12);
    printf("               3. 대중교통              ");
    gotoxy(42, 13);
    printf("               4. 자전거                ");
    */


    gotoxy(42, 24);
    printf("========================================");
}


void sub2page()
{
    s();
    gotoxy(42, 5);
    printf("========================================");
    gotoxy(42, 6);
    printf("       1. 서울    |   2. 강릉           ");
    gotoxy(42, 7);
    printf("========================================");
    gotoxy(42, 8);
    printf("       3. 천안    |   4. 청주           ");
    gotoxy(42, 9);
    printf("========================================");
    gotoxy(42, 10);
    printf("       5. 대전    |   6. 논산           ");
    gotoxy(42, 11);
    printf("========================================");
    gotoxy(42, 12);
    printf("       7, 포항    |   8. 대구          ");
    gotoxy(42, 13);
    printf("========================================");
    gotoxy(42, 14);
    printf("       9. 광주    |   10. 부산          ");
    gotoxy(42, 15);
    printf("========================================");
}

void sub3page()
{
    s();
    gotoxy(42, 5);
    printf("========================================");
    gotoxy(42, 6);
    printf("            즐겨찾기 목록               ");

    gotoxy(42, 18);
    printf("========================================");
}
void RP()
{
    FILE* fp = fopen("Recent Paths.txt", "r");
    if (fp != NULL)
    {
        char line[100];
        int lineCount = 0;
        while (fgets(line, sizeof(line), fp) != NULL && lineCount < 5)
        {
            gotoxy(42, 8 + lineCount);
            printf("%s", line);
            lineCount++;
        }
        fclose(fp);
    }
}
void sub4page()
{
    s();
    gotoxy(42, 5);
    printf("========================================");
    gotoxy(42, 6);
    printf("              최근 기록               ");
    RP();
    gotoxy(42, 14);
    printf("========================================");
    gotoxy(42, 18);
    printf("please press the enter...");
}


void mainpage()
{
    s();

    gotoxy(42, 7);
    printf("========================================");
    gotoxy(42, 8);
    printf("       안녕하세요 U_R 맵입니다.");
    gotoxy(42, 9);
    printf("         무엇을 도와드릴까요?");
    gotoxy(42, 10);
    printf("========================================");


    printMenu(42, 12);  // 메뉴 출력

    point(40, 12);  // 메뉴 선택

    if (selectedOption == 1) {
        // 길 찾기 옵션 선택 시 처리할 작업 추가
        system("cls");
        sub1page();
        menu1();
    }
    else if (selectedOption == 2) {
        // 즐겨찾기 추가 옵션 선택 시 처리할 작업 추가
        system("cls");
        sub2page();
        menu2();
    }
    else if (selectedOption == 3) {
        // 즐겨찾기 삭제 옵션 선택 시 처리할 작업 추가
        system("cls");
        sub3page();
        menu3();
    }
    else if (selectedOption == 4) {
        // 최근 기록 옵션 선택 시 처리할 작업 추가
        system("cls");
        sub4page();
    }
    else if (selectedOption == 5) {
        system("cls");  // 화면 지우고 새로운 UI 페이지로 넘어감
        s();
        gotoxy(43, 12);
        printf("========================================");
        gotoxy(44, 13);
        printf("       이용해주셔서 감사합니다.");
        gotoxy(43, 14);
        printf("            함수를 종료합니다.");
        gotoxy(43, 15);
        printf("========================================");
        return;  // 함수 종료
    }
}

int main(void) {
    int people = 0;
    while (1) {
        system("cls");  // 화면을 지우고 새로운 UI 페이지로 넘어감
        mainpage();
        _getch();
        if (selectedOption == 5) {
            break;  // 반복문 종료
        }
    }
    return 0;
}