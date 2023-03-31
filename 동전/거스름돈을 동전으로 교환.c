#include <stdio.h>

void changecoin(int coin)  // 동전 교환 함수 (changecoin)를 정의
{
	int recoin;             //잔돈 변수    coin만 사용해도 좋지만 시인성이 좋지 않다고 판단 recoin을 사용
	int w500, w100, w50, w10;		//각 동전의 변수

	w500 = coin / 500;		//500원 동전의 개수를 계산
	printf("오백원짜리 ==> %d 개 \n", w500);		//계산한 동전을 출력
	recoin = coin % 500;		//잔돈에서 500원을 나눈것을 제외한 금액   

	w100 = recoin / 100;
	printf("백원짜리    ==> %d 개 \n", w100);
	recoin = recoin % 100;

	w50 = recoin / 50;
	printf("오십원짜리 ==> %d 개 \n", w50);
	recoin = recoin % 50;

	w10 = recoin / 10;
	printf("십원짜리    ==> %d 개 \n", w10);
	recoin = recoin % 10;

	printf("바꾸지 못한 잔돈 ==> %d 원 \n", recoin);		//각 동전들로는 바꾸지 못하는 1자리 수의 동전
}

int main() {

	int coin;
	printf("교환할 돈은 ? ");
	scanf("%d", &coin);

	changecoin(coin);		//위에 교환하는 함수 호출

	return 0;
}