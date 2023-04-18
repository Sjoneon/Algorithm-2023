#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:4244)
#pragma warning(disable:4101)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100

typedef struct Man {
	char name[10];
	double tArrive;
}Man;

Man boy[MAX_QUEUE_SIZE];
Man girl[MAX_QUEUE_SIZE];

int boyf, girlf;
int boyr, girlr;

char mans[10][10] = { "남자원","남자투","남자셋","남자넷","남자오","남자육","남자칠" };
char womans[10][10] = { "여자원","여자투","여자셋","여자넷","여자오","여자육","여자칠" };

int nSimulation;
int Wait_boy;
int Wait_girl;
int boy_n;
int girl_n;
int nServedCouple;

double probArrival;

void error(char* str) {
	printf("%s\n", str);
	exit(1);
}

void M_init_queue() { boyf = boyr = 0; }
int M_is_empty() { return boyf == boyr; }
int M_is_full() { return boyf == (boyr + 1) % MAX_QUEUE_SIZE; }
int M_size() { return (boyr - boyf + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void W_init_queue() { girlf = girlr = 0; }
int W_is_empty() { return girlf == girlr; }
int W_is_full() { return girlf == (girlr + 1) % MAX_QUEUE_SIZE; }
int W_size() { return (girlr - girlf + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

Man Mdequeue()
{
	if (M_is_empty())
		error(" 큐 공백 에러");
	boyf = (++boyf) % MAX_QUEUE_SIZE;
	return boy[boyf];
}
Man Mpeek()
{
	if (M_is_empty())
		error(" 큐 공백 에러");
	return boy[(++boyf) % MAX_QUEUE_SIZE];
}
void Menqueue(Man val)
{
	if (M_is_full())
		error("큐 포화 에러");
	boyr = (++boyr) % MAX_QUEUE_SIZE;
	boy[boyr] = val;
}

Man Wdequeue()
{
	if (W_is_empty())
		error(" 큐 공백 에러");
	girlf = (++girlf) % MAX_QUEUE_SIZE;
	return girl[girlf];
}
Man Wpeek()
{
	if (W_is_empty())
		error(" 큐 공백 에러");
	return girl[(++girlf) % MAX_QUEUE_SIZE];
}
void Wenqueue(Man val)
{
	if (W_is_full())
		error("큐 포화 에러");
	girlr = (++girlr) % MAX_QUEUE_SIZE;
	girl[girlr] = val;
}

void insert_human(int tArrive) {
	Man a;
	a.tArrive = tArrive;

	if (rand() % 2 == 0) {
		strcpy(a.name, mans[rand() % 7]);
		Menqueue(a);
		boy_n++;
		printf("남학생 등록: %s", a.name);
	}
	else {
		strcpy(a.name, womans[rand() % 7]);
		Wenqueue(a);
		girl_n++;
		printf("여학생 등록: %s", a.name);
	}
}

void read_sim_params()
{
	printf("시뮬레이션 할 최대 시간 (예:20) : ");
	scanf("%d", &nSimulation);

	printf("단위 시간에 도착하는 고객 수 (예: 0.3) = ");
	scanf("%lf", &probArrival);

	printf("===============================================\n");
}

double rand0to1() { return rand() / (double)RAND_MAX; }

void run_simulation() {
	Man a;
	int clock = 0;

	W_init_queue();
	M_init_queue();

	while (clock < nSimulation) {
		clock++;
		printf("[ %d]: ", clock);
		if (rand0to1() < probArrival)
			insert_human(clock);

		if (W_is_empty() || M_is_empty()) {
			printf("\n");
		}
		else {
			Man the_boy = Mdequeue();
			Man the_girl = Wdequeue();
			int bwait = clock - the_boy.tArrive;
			int gwait = clock - the_girl.tArrive;
			printf(" ==> 커플탄생! %s♥%s (%d,%d 기다림)\n", the_boy.name, the_girl.name, bwait, gwait);
			Wait_boy += bwait;
			Wait_girl += gwait;
			nServedCouple++;
		}
	}
}

void print_result() {
	printf("====================================================\n");
	printf(" 서비스 받은 커플수 = %d\n", nServedCouple);
	printf(" 현재 대기 남학생 수 = %d\n", boy_n - nServedCouple);
	printf(" 현재 대기 여학생 수 = %d\n", girl_n - nServedCouple);
	printf(" 전체 남학생 대기시간 = %d\n", Wait_boy);
	printf(" 전체 여학생 대기시간 = %d\n", Wait_girl);
	printf(" 남학생 평균대기시간 = %-5.2f\n", (double)Wait_boy / boy_n);
	printf(" 남학생 평균대기시간 = %-5.2f\n", (double)Wait_girl / girl_n);
}

int main() {
	srand((unsigned int)time(NULL));
	read_sim_params();
	run_simulation();
	print_result();
	return 0;
}