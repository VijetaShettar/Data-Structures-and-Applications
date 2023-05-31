#include<stdio.h>
#include<stdlib.h>

void read_matrix(float a[100][100], int row, int col);
void display_matrix(float a[100][100], int row, int col);
int is_symmetric(float a[100][100], int row, int col);

int main()
{
    float a[100][100];
    int row;
    int col;
    int test;

    printf("Enter number of rows and columns:\n");
    test = scanf("%d%d", &row, &col);

    if(test != 2)
    {
        printf("Enter valid data\n");
        exit(0);
    }

    if(row <= 0 || col <= 0)
    {
        printf("Order of matrix should be greater than Zero\n");
    }
    else if(row > 100 || col > 100)
    {
        printf("Order of matrix should be less than 100 X 100\n");
    }
    else
    {
        read_matrix(a, row, col);
        display_matrix(a, row, col);

        if(is_symmetric(a, row, col))
        {
            printf("The matrix is symmetric.\n");
        }
        else
        {
            printf("The matrix is not symmetric.\n");
        }
    }

    return 0;
}

void read_matrix(float a[100][100], int row, int col)
{
    int i, j;
    int test;

    printf("Enter matrix elements:\n");

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            test = scanf("%f", &a[i][j]);

            if(test != 1)
            {
                printf("Enter valid data\n");
                exit(0);
            }
        }
    }
}

void display_matrix(float a[100][100], int row, int col)
{
    int i, j;

    printf("Matrix:\n");

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%f\t", a[i][j]);
        }
        printf("\n");
    }
}

int is_symmetric(float a[100][100], int row, int col)
{
    int i, j;

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(a[i][j] != a[j][i])
            {
                return 0;  // Not symmetric
            }
        }
    }

    return 1;  // Symmetric
}
