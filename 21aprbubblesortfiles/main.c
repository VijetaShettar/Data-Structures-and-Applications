#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp1, *fp2;
    int *numbers, i, j, temp, n;
    fp1 = fopen("numbers.txt", "r");
    if(fp1 == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    printf("Enter the number of integers to sort: ");
    scanf("%d", &n);
    numbers = (int*) malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
    {
        fscanf(fp1, "%d", &numbers[i]);
    }
    fclose(fp1);
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(numbers[j] > numbers[j+1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }

    fp2 = fopen("sort.txt", "w");
    if(fp2 == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    for(i = 0; i < n; i++)
    {
        fprintf(fp2, "%d ", numbers[i]);
    }
    fclose(fp2);
    free(numbers);

    return 0;
}
