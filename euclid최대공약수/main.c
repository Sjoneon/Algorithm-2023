#include <stdio.h>
#include <time.h>

int testeuclid();

int main()
{
	int ret = 0;

	clock_t start, finish;	// clock_t Ÿ���� start�� finish ������ �����Ѵ�.
	double duration;

	start = clock();	// ���α׷� ���� �ð��� ����

	printf("Hello World\n");

	ret = testeuclid();	//���ʿ� �Լ� ȣ���ϰ� ret�� ����

	finish = clock();	//���α׷� ���� �ð��� ����

	duration = (double)(finish - start) / CLOCKS_PER_SEC;	//������ ����, ���� �ð��� ����Ѵ�.

	printf("%.10f���Դϴ�.", duration);	//�Ҽ��� 10�ڸ����� �ɸ� �ð��� ����Ѵ�.

	return 0;

}