//����� �ִ����� �˰���
int euclidRecalsive(int a, int b)
{
    if (b == 0) 
    {
        return a;
    }
    else 
    {
        return euclidRecalsive(b, a % b);
    }
}


//�ݺ��� �ִ����� �˰���
int euclidRepetitive(int a, int b)
{
    int n=0;

    while (b != 0) 
    {
        n = a % b;
        a = b;
        b = n;
    }
    return a;
}