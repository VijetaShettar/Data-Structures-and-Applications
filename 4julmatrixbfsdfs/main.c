#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define QUEUE_SIZE 100

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue *queue) {
    return queue->front == -1;
}

int isQueueFull(Queue *queue) {
    return (queue->rear + 1) % QUEUE_SIZE == queue->front;
}

void enqueue(Queue *queue, int value) {
    if (isQueueFull(queue)) {
        printf("Queue is full.\n");
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->items[queue->rear] = value;
}

int dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int value = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % QUEUE_SIZE;
    }
    return value;
}

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

void bfs(int startVertex, int numVertices, int adjacencyMatrix[][MAX_VERTICES], FILE *file) {
    int visited[MAX_VERTICES] = {0};
    Queue queue;
    initializeQueue(&queue);

    visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    fprintf(file, "BFS Search:\n");
    while (!isQueueEmpty(&queue)) {
        int currentVertex = dequeue(&queue);
        fprintf(file, "%d ", currentVertex + 1);

        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                enqueue(&queue, i);
                visited[i] = 1;
            }
        }
    }
    fprintf(file, "\n");
}

void dfsRecursive(int currentVertex, int numVertices, int adjacencyMatrix[][MAX_VERTICES], int visited[], FILE *file) {
    visited[currentVertex] = 1;
    fprintf(file, "%d ", currentVertex + 1);

    for (int i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
            dfsRecursive(i, numVertices, adjacencyMatrix, visited, file);
        }
    }
}

void dfs(int startVertex, int numVertices, int adjacencyMatrix[][MAX_VERTICES], FILE *file) {
    int visited[MAX_VERTICES] = {0};

    fprintf(file, "DFS Search:\n");
    dfsRecursive(startVertex, numVertices, adjacencyMatrix, visited, file);
    fprintf(file, "\n");
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    FILE *bfsOutputFile = fopen("bfs_output.txt", "w");
    FILE *dfsOutputFile = fopen("dfs_output.txt", "w");

    int numVertices, numEdges;
    int edges[MAX_VERTICES][2];
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    if (inputFile == NULL || outputFile == NULL || bfsOutputFile == NULL || dfsOutputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    readGraph(inputFile, &numVertices, &numEdges, edges);
    createAdjacencyMatrix(numVertices, numEdges, edges, adjacencyMatrix);
    writeAdjacencyMatrixToFile(outputFile, numVertices, adjacencyMatrix);
    bfs(0, numVertices, adjacencyMatrix, bfsOutputFile);
    dfs(0, numVertices, adjacencyMatrix, dfsOutputFile);

    fclose(inputFile);
    fclose(outputFile);
    fclose(bfsOutputFile);
    fclose(dfsOutputFile);

    return 0;
}
