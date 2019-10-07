int sum_by_rows(int **mas, int N, int M)
{
    volatile int sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            sum = sum + mas[i][j];
    return sum;
}