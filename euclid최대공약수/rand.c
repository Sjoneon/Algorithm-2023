void randomcall(int a[], int b[])
{
	for (int i = 0; i < 1000; i++)
	{
		int rad = 0;

        a[i] = rand() % 10000;  // 0부터 9999까지의 랜덤한 정수를 반환
        b[i] = rand() % 10000;  // 0부터 9999까지의 랜덤한 정수를 반환

        if (b[i] > a[i])    // b[i]가 a[i]보다 큰 경우
        {
            int rad = a[i]; // a[i]와 b[i]를 내용물을 서로 바꿔준다.
            a[i] = b[i];
            b[i] = rad;
        }
    }

}