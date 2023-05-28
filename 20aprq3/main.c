#include <stdio.h>

void read(int a[100][100], int r1, int c1);
void output(int b[100][100], int r2, int c2);
void mult(int a[100][100], int b[100][100], int r1, int c1, int r2, int c2);

int main()
{
    int r1, r2, c1, c2, a[100][100], b[100][100];

    printf("Enter row and column of mat1:\t");
    scanf("%d %d", &r1, &c1);

    printf("Enter row and column of mat2:\t");
    scanf("%d %d", &r2, &c2);

    printf("Enter matrix1:\n");
    read(a, r1, c1);

    printf("Enter matrix2:\n");
    read(b, r2, c2);

    printf("Display:\n");
    output(a, r1, c1);
    printf("\n");
    output(b, r2, c2);

    printf("Multiplication of two matrices:\n");
    mult(a, b, r1, c1, r2, c2);

    return 0;
}

void read(int a[100][100], int r1, int c1)
{
    int i, j;
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

void output(int a[100][100], int r1, int c1)
{
    int i, j;
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

void mult(int a[100][100], int b[100][100], int r1, int c1, int r2, int c2)
{
    if (c1 != r2)
    {
        printf("Matrix multiplication not possible.\n");
        return;
    }

    int i, j, k;
    int sum, res[100][100];

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            sum = 0;
            for (k = 0; k < r2; k++)
            {
                sum = sum + a[i][k] * b[k][j];
            }
            res[i][j] = sum; // save sum in resultant matrix
        }
    }

    output(res, r1, c2);
}

