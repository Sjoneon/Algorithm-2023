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

char mans[10][10] = { "���ڿ�","������","���ڼ�","���ڳ�","���ڿ�","������","����ĥ" };
char womans[10][10] = { "���ڿ�","������","���ڼ�","���ڳ�","���ڿ�","������","����ĥ" };

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
		error(" ť ���� ����");
	boyf = (++boyf) % MAX_QUEUE_SIZE;
	return boy[boyf];
}
Man Mpeek()
{
	if (M_is_empty())
		error(" ť ���� ����");
	return boy[(++boyf) % MAX_QUEUE_SIZE];
}
void Menqueue(Man val)
{
	if (M_is_full())
		error("ť ��ȭ ����");
	boyr = (++boyr) % MAX_QUEUE_SIZE;
	boy[boyr] = val;
}

Man Wdequeue()
{
	if (W_is_empty())
		error(" ť ���� ����");
	girlf = (++girlf) % MAX_QUEUE_SIZE;
	return girl[girlf];
}
Man Wpeek()
{
	if (W_is_empty())
		error(" ť ���� ����");
	return girl[(++girlf) % MAX_QUEUE_SIZE];
}
void Wenqueue(Man val)
{
	if (W_is_full())
		error("ť ��ȭ ����");
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
		printf("���л� ���: %s", a.name);
	}
	else {
		strcpy(a.name, womans[rand() % 7]);
		Wenqueue(a);
		girl_n++;
		printf("���л� ���: %s", a.name);
	}
}

void read_sim_params()
{
	printf("�ùķ��̼� �� �ִ� �ð� (��:20) : ");
	scanf("%d", &nSimulation);

	printf("���� �ð��� �����ϴ� �� �� (��: 0.3) = ");
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
			printf(" ==> Ŀ��ź��! %s��%s (%d,%d ��ٸ�)\n", the_boy.name, the_girl.name, bwait, gwait);
			Wait_boy += bwait;
			Wait_girl += gwait;
			nServedCouple++;
		}
	}
}

void print_result() {
	printf("====================================================\n");
	printf(" ���� ���� Ŀ�ü� = %d\n", nServedCouple);
	printf(" ���� ��� ���л� �� = %d\n", boy_n - nServedCouple);
	printf(" ���� ��� ���л� �� = %d\n", girl_n - nServedCouple);
	printf(" ��ü ���л� ���ð� = %d\n", Wait_boy);
	printf(" ��ü ���л� ���ð� = %d\n", Wait_girl);
	printf(" ���л� ��մ��ð� = %-5.2f\n", (double)Wait_boy / boy_n);
	printf(" ���л� ��մ��ð� = %-5.2f\n", (double)Wait_girl / girl_n);
}

int main() {
	srand((unsigned int)time(NULL));
	read_sim_params();
	run_simulation();
	print_result();
	return 0;
}