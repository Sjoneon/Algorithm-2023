void randomcall(int a[], int b[])
{
	for (int i = 0; i < 1000; i++)
	{
		int rad = 0;

        a[i] = rand() % 10000;  // 0���� 9999������ ������ ������ ��ȯ
        b[i] = rand() % 10000;  // 0���� 9999������ ������ ������ ��ȯ

        if (b[i] > a[i])    // b[i]�� a[i]���� ū ���
        {
            int rad = a[i]; // a[i]�� b[i]�� ���빰�� ���� �ٲ��ش�.
            a[i] = b[i];
            b[i] = rad;
        }
    }

}