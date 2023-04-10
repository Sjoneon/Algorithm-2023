#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand.h"	//rand.h 파일을 포함시킨다.
#include "euclid.h"		//euclib.h 파일을 포함시킨다.

int testeuclid()
{

	int r_arr1[10000] = { 0 };	//크기가 10000인 배열 선언 후 0으로 초기화
	int r_arr2[10000] = { 0 };

	int gcd[10000] = { 0 };


	srand(time(NULL));	//현재 시간을 기준으로 난수 발생을 초기화

	randomcall(r_arr1, r_arr2);	//두 배열에 랜덤값 저장

	for (int i = 0; i < 1000; i++)
	{
		gcd[i] = euclidRepetitive(r_arr1[i], r_arr2[i]);	// 반복
		//gcd[i] = euclidRecalsive(r_arr1[i], r_arr2[i]);	// 재귀
	}

	for (int i = 0; i < 1000; i++)
	{
		printf("%d와%d 의 최대공약수는 %d 입니다.\n", r_arr1[i], r_arr2[i], gcd[i]);
	}

	return 0;

	// 다른거 없이 euclid.c 만들고 rand.c 같은거 없을때,
	//딱 1.Euclid 최대공약수 알고리즘을 재귀적 방법과 반복적 방법으로 2가지 함수로 각각 구현하고 테스트 코드를 작성하시오.
	//할때 확인용으로만 쓰던거
	/*
	int gcd = 0;
	int abc = 0;
	printf("안녕하세요. 테스트합니다. \n");


	gcd = euclidRecalsive(24, 12);

	printf("%d와%d 의 최대공약수는 %d 입니다.\n", 24, 12, gcd);


	abc = euclidRepetitive(24, 12);

	printf("%d와%d 의 최대공약수는 %d 입니다.\n", 24, 12, abc);

	return 0;
	*/
}