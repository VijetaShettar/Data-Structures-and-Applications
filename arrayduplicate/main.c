#include<stdio.h>
#include<stdlib.h>
#define MAX 100

void readArray(int a[], int N);
void displayArray(int a[], int N);

int main()
{
    int a[MAX];
    int N;
    int test;
    printf("Enter the size of the array\n");
    test = scanf("%d", &N);
    if (test != 1)
    {
        printf("Enter integers only\n");
        exit(0);
    }
    else if (N <= 0)
        printf("size of the array should be positive\n");
    else if (N > MAX)
        printf("size of the array should be less than %d\n", MAX);
    else
    {
        printf("Enter array elements\n");
        readArray(a, N);
        printf("Array before deleting duplicates : \n");
        displayArray(a, N);

        // Identify duplicate elements and print their occurrence count
        int count[MAX] = {0};  // Array to store occurrence count of each element
        int uniqueN = 0;       // Number of unique elements
        for (int i = 0; i < N; i++)
        {
            int found = 0;
            for (int j = 0; j < uniqueN; j++)
            {
                if (a[i] == a[j])
                {
                    found = 1;
                    count[j]++;
                    break;
                }
            }
            if (!found)
            {
                a[uniqueN] = a[i];
                count[uniqueN] = 1;
                uniqueN++;
            }
        }

        printf("Array after deleting duplicates : \n");
        for (int i = 0; i < uniqueN; i++)
        {
            printf("%d (occurs %d times)\n", a[i], count[i]);
        }
    }
    return 0;
}

void readArray(int a[], int N)
{
    int i;
    int test;
    for (i = 0; i < N; i++)
    {
        test = scanf("%d", &a[i]);
        if (test != 1)
        {
            printf("Enter valid data\n");
            exit(0);
        }
    }
}

void displayArray(int a[], int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d\n", a[i]);
    }
}
