#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 
#include "dijkstra.h"
#include "menu.h"
#include "menu1.h"


void load_road_Region(char* filename);
void You_Find_Road();
int start_point();
int end_point();
int Transport();
void T_R_Result();
void save_recent_path(char start[], char finish[]);


void load_road_Region(char* filename)
{
	int i;
	char Reg[100];
	FILE* fp = fopen(filename, "r");
	if (fp != NULL)
	{
		//printf("파일 열기 성공\n");
	}
	else
	{
		//printf("파일 열기 실패\n");
		return; // 파일 열기 실패 시 함수 종료
	}

	for (i = 0; i < 10; i++)
	{
		if (fgets(Reg, sizeof(Reg) + 1, fp) != NULL) // 한 줄씩 읽기
		{
			char* token = strtok(Reg, "("); // "(" 전까지 token으로 저장
			if (token != NULL) // 읽어드렸으면
				strncpy(R[i].region, token, sizeof(R[i].region)); // 문자열 복사

			token = strtok(NULL, ")");
			if (token != NULL)
				strncpy(R[i].nickname, token, sizeof(R[i].nickname));
		}
		else
		{
			break; // 파일의 끝에 도달한 경우 반복문 종료
		}
	}
	fclose(fp); // 파일 닫기
}


void You_Find_Road()
{
	char* start;
	char* finish;

	load_wgraph("weight.txt");

	load_road_Region("Region.txt");
	printf("\n");
	start = start_point();

	finish = end_point();

	T_R_Result(start, finish);

}

int start_point()
{
	char* start_reg[5];
	int i;
	int start_pos = -1;

	gotoxy(42, 6);
	printf("            출발지 : ");
	scanf("%s", start_reg);

	for (i = 0; i < vsize; i++)
	{
		if (strcmp(start_reg, R[i].region) == 0 || strcmp(start_reg, R[i].nickname) == 0)
		{
			start_pos = i;
			//printf("출발지 고른 위치 : %d\n", start_pos);
		}
	}
	if (start_pos == -1)
	{

		gotoxy(60, 6);
		printf("                  ");


		gotoxy(40, 25);
		printf("이 지역은 U_R 맵에 해당하지 않는 지역입니다.");
		gotoxy(52, 26);
		printf("다시 입력해주십시오.\n");
		start_point();
	}
	else
	{
		gotoxy(40, 25);
		printf("                                               ");
		gotoxy(52, 26);
		printf("                             ");

		return start_pos;
	}
}

int end_point()
{
	char* finish_reg[5];
	int i;
	int finish_pos = -1;
	

	gotoxy(42, 7);
	printf("            도착지 : ");
	scanf("%s", finish_reg);

	for (i = 0; i < vsize; i++)
	{
		if (strcmp(finish_reg, R[i].region) == 0 || strcmp(finish_reg, R[i].nickname) == 0)
		{
			finish_pos = i;
		}
	}
	if (finish_pos == -1)
	{
		
		gotoxy(60, 7);
		printf("                  ");

		gotoxy(40, 25);
		printf("이 지역은 U_R 맵에 해당하지 않는 지역입니다.");
		gotoxy(52, 26);
		printf("다시 입력해주십시오.\n");

		end_point();
	}
	else
	{
		gotoxy(40, 25);
		printf("                                               ");
		gotoxy(52, 26);
		printf("                             ");
		
		return finish_pos;
	}
}

int Transport()
{
	int num = 0;

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
	gotoxy(42, 14);
	printf(">> ");
	scanf("%d", &num);

	if (num == 1 || num == 2 || num == 3 || num == 4)
	{
		return num;
	}
	else
	{
		gotoxy(40, 25);
		printf("번호를 잘못입력하셨습니다. 다시 입력해주십시오.");

		gotoxy(44, 14);
		printf("  ");
		gotoxy(44, 13);
		Transport();
		gotoxy(40, 25);
		printf("                                               "); 
	}
}

void T_R_Result(int start, int end)
{
	int Trans_num = Transport();
	char Trans[20] = "\0";
	int dist = print_shortest_path(start, end);

	time_t timer = time(NULL); // 현재시간 출력해주는 시간함수
	struct tm* t = localtime(&timer);

	double minute = 0.6 * (double)dist * 1.0;// 교통수단 때 배수를 곱하기 위해서
	int hour = minute / 60;

	minute = minute - (hour * 60);

	// 교통수단 당 배수를 곱하면서 거리 계산
	if (Trans_num == 1)
	{
		strcpy(Trans, "도보");
		hour *= 15;
		// 여기서 대충 거리당 몇분 걸리는지 정하면 곱해주면 됨
		// 일단 그냥 쉽게 자동차 기준으로 1.5km당 1분 걸린다고 하자
		// 개인적인 생각인데 자동차를 기준으로 다른걸 줄이는게 나을 수도 있다.
	}
	else if (Trans_num == 2)
	{
		strcpy(Trans, "자동차");
		hour *= 1.0;
	}
	else if (Trans_num == 3)
	{
		strcpy(Trans, "대중교통");
		hour *= 1.5;
		// 랜덤으로 3개정도 만든다음 근처에 버스가 없으면 10분을 더한다.
		// 시간 상 없는 관계로 패스
	}
	else if (Trans_num == 4)
	{
		strcpy(Trans, "자전거");
		hour *= 5;
	}

	gotoxy(42, 15);
	printf("========================================"); // 결과창 UI를 옮겨주는 커서함수
	gotoxy(42, 16);

	if (strcmp(R[start].nickname, " ") == 0) // 앞 별명 없음
	{
		if (strcmp(R[end].nickname, " ") == 0) // 뒤 별명 없음
			printf("%s → %s까지 ", R[start].region, R[end].region);
		else // 뒤 별명 있음
			printf("%s → %s(%s)까지 ", R[start].region, R[end].nickname, R[end].region);
	}
	else // 앞 별명 있음
	{
		if (strcmp(R[end].nickname, " ") == 0)   // 뒤 별명 없음
			printf("%s(%s) → %s까지 ", R[start].nickname, R[start].region, R[end].region);
		else // 뒤 별명 있음
			printf("%s(%s) → %s(%s)까지 ", R[start].nickname, R[start].region, R[end].nickname, R[end].region);
	}
	gotoxy(42, 17);
	printf("%s 이동 시, 거리 %dkm, 소요시간 %d시간 %.0lf분\n\n", Trans, dist, hour, minute);
	// minute는 출력할 땐 정수로 바꿀 예정

	int new_min = (t->tm_min) + (int)minute;
	int new_hour = ((t->tm_hour) + hour + (new_min / 60)) % 24;
	new_min = new_min % 60;

	gotoxy(42, 18);
	printf("현재 시간 : %d시 %d분, 도착 시간 : %d시 %d분", t->tm_hour, t->tm_min, new_hour, new_min);

	save_recent_path(start, end, hour, minute);

	_getch();

	return 0;
}

void save_recent_path(int start, int finish, int hour, double minute)
{
	FILE* fp = fopen("Recent Paths.txt", "a");
	if (fp != NULL)
	{
		fprintf(fp, "%s -> %s / 소요시간 %d시간 %.0lf분\n", R[start].region, R[finish].region, hour, minute);
		fclose(fp);
		gotoxy(42, 20);
		printf("최근 경로가 성공적으로 저장되었습니다.\n");
	}
	else
	{
		printf("파일을 열 수 없습니다. 최근 경로를 저장하지 못했습니다.\n");
	}
}

void menu1()
{
	You_Find_Road();
}