#include <stdio.h>

#define SIZE 3

void matrixMultiplication(int* matrix1, int* matrix2, int* result) {
    int i, j, k;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            *(result + i * SIZE + j) = 0;
            for (k = 0; k < SIZE; k++) {
                *(result + i * SIZE + j) += *(matrix1 + i * SIZE + k) * *(matrix2 + k * SIZE + j);
            }
        }
    }
}

void printMatrix(int* matrix) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d ", *(matrix + i * SIZE + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int matrix1[SIZE][SIZE];
    int matrix2[SIZE][SIZE];
    int result[SIZE][SIZE];

    printf("Enter the elements of Matrix 1 (%dx%d):\n", SIZE, SIZE);
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter the elements of Matrix 2 (%dx%d):\n", SIZE, SIZE);
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    matrixMultiplication(&matrix1[0][0], &matrix2[0][0], &result[0][0]);

    printf("\nMatrix 1:\n");
    printMatrix(&matrix1[0][0]);

    printf("Matrix 2:\n");
    printMatrix(&matrix2[0][0]);

    printf("Result:\n");
    printMatrix(&result[0][0]);

    return 0;
}
