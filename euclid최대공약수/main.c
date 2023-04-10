#include <stdio.h>
#include <time.h>

int testeuclid();

int main()
{
	int ret = 0;

	clock_t start, finish;	// clock_t 타입의 start와 finish 변수를 선언한다.
	double duration;

	start = clock();	// 프로그램 시작 시간을 저장

	printf("Hello World\n");

	ret = testeuclid();	//왼쪽에 함수 호출하고 ret에 저장

	finish = clock();	//프로그램 종료 시간을 저장

	duration = (double)(finish - start) / CLOCKS_PER_SEC;	//저장한 시작, 종료 시간을 계산한다.

	printf("%.10f초입니다.", duration);	//소수점 10자리까지 걸린 시간을 출력한다.

	return 0;

}