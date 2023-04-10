#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand.h"	//rand.h ������ ���Խ�Ų��.
#include "euclid.h"		//euclib.h ������ ���Խ�Ų��.

int testeuclid()
{

	int r_arr1[10000] = { 0 };	//ũ�Ⱑ 10000�� �迭 ���� �� 0���� �ʱ�ȭ
	int r_arr2[10000] = { 0 };

	int gcd[10000] = { 0 };


	srand(time(NULL));	//���� �ð��� �������� ���� �߻��� �ʱ�ȭ

	randomcall(r_arr1, r_arr2);	//�� �迭�� ������ ����

	for (int i = 0; i < 1000; i++)
	{
		gcd[i] = euclidRepetitive(r_arr1[i], r_arr2[i]);	// �ݺ�
		//gcd[i] = euclidRecalsive(r_arr1[i], r_arr2[i]);	// ���
	}

	for (int i = 0; i < 1000; i++)
	{
		printf("%d��%d �� �ִ������� %d �Դϴ�.\n", r_arr1[i], r_arr2[i], gcd[i]);
	}

	return 0;

	// �ٸ��� ���� euclid.c ����� rand.c ������ ������,
	//�� 1.Euclid �ִ����� �˰����� ����� ����� �ݺ��� ������� 2���� �Լ��� ���� �����ϰ� �׽�Ʈ �ڵ带 �ۼ��Ͻÿ�.
	//�Ҷ� Ȯ�ο����θ� ������
	/*
	int gcd = 0;
	int abc = 0;
	printf("�ȳ��ϼ���. �׽�Ʈ�մϴ�. \n");


	gcd = euclidRecalsive(24, 12);

	printf("%d��%d �� �ִ������� %d �Դϴ�.\n", 24, 12, gcd);


	abc = euclidRepetitive(24, 12);

	printf("%d��%d �� �ִ������� %d �Դϴ�.\n", 24, 12, abc);

	return 0;
	*/
}