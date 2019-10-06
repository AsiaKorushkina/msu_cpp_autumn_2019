int sum_by_col(int **mas, int N, int M)
{
    int sum = 0;
    for (int j = 0; j < M; j++)
        for (int i = 0; i < N; i++)
            sum = sum + mas[i][j];
    return sum;
}