#include <stdio.h>

int main(void)
{
	int money;
	int c500, c100, c10;
	int n;

	printf("거스름돈을 입력받으세요 : \n");
	scanf("%d", &money);

	if (money >= 500)
		c500 = money % 500;
	printf("500: % d", &c500);
	else if (100 >= money > 500)
		c100 = money % 100;
	printf("100: % d", &c100);
	else if (10 >= money > 100)
		c10 = money % 10;
	printf("10: % d", &c10);
	else
		printf("나머지: % d", &n);
	break;

	return 0;
}