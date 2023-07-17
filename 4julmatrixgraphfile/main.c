#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void readGraph(FILE *file, int *numVertices, int *numEdges, int edges[][2]) {
    fscanf(file, "%d %d", numVertices, numEdges);

    for (int i = 0; i < *numEdges; i++) {
        fscanf(file, "%d %d", &edges[i][0], &edges[i][1]);
    }
}

void createAdjacencyMatrix(int numVertices, int numEdges, int edges[][2], int matrix[][MAX_VERTICES]) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < numEdges; i++) {
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        matrix[v1 - 1][v2 - 1] = 1;
        matrix[v2 - 1][v1 - 1] = 1;
    }
}

void writeAdjacencyMatrixToFile(FILE *file, int numVertices, int matrix[][MAX_VERTICES]) {
    fprintf(file, "Adjacency Matrix:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    int numVertices, numEdges;
    int edges[MAX_VERTICES][2];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    readGraph(inputFile, &numVertices, &numEdges, edges);
    createAdjacencyMatrix(numVertices, numEdges, edges, adjacencyMatrix);
    writeAdjacencyMatrixToFile(outputFile, numVertices, adjacencyMatrix);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
