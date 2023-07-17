#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList[MAX_VERTICES];

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(AdjList adjList, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjList[src].head;
    adjList[src].head = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest].head;
    adjList[dest].head = newNode;
}

void printAdjacencyList(AdjList adjList, int numVertices, FILE* outputFile) {
    int i;
    for (i = 1; i <= numVertices; ++i) {
        Node* temp = adjList[i].head;
        fprintf(outputFile, "Adjacency list of vertex %d\n", i);
        while (temp) {
            fprintf(outputFile, "%d ", temp->vertex);
            temp = temp->next;
        }
        fprintf(outputFile, "\n");
    }
}

void DFSUtil(AdjList adjList, int vertex, int visited[], FILE* outputFile) {
    visited[vertex] = 1;
    fprintf(outputFile, "%d ", vertex);

    Node* temp = adjList[vertex].head;
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(adjList, adjVertex, visited, outputFile);
        }
        temp = temp->next;
    }
}

void DFS(AdjList adjList, int numVertices, FILE* outputFile) {
    int visited[MAX_VERTICES] = {0};

    fprintf(outputFile, "DFS Traversal: ");
    for (int i = 1; i <= numVertices; ++i) {
        if (!visited[i]) {
            DFSUtil(adjList, i, visited, outputFile);
        }
    }
    fprintf(outputFile, "\n");
}

void BFS(AdjList adjList, int numVertices, FILE* outputFile) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = -1, rear = -1;

    fprintf(outputFile, "BFS Traversal: ");

    for (int i = 1; i <= numVertices; ++i) {
        if (!visited[i]) {
            visited[i] = 1;
            queue[++rear] = i;

            while (front != rear) {
                int vertex = queue[++front];
                fprintf(outputFile, "%d ", vertex);

                Node* temp = adjList[vertex].head;
                while (temp) {
                    int adjVertex = temp->vertex;
                    if (!visited[adjVertex]) {
                        visited[adjVertex] = 1;
                        queue[++rear] = adjVertex;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    fprintf(outputFile, "\n");
}

void freeAdjacencyList(AdjList adjList, int numVertices) {
    int i;
    for (i = 1; i <= numVertices; ++i) {
        Node* temp = adjList[i].head;
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main() {
    FILE* inputFile = fopen("graph_input.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    FILE* adjacencyListOutput = fopen("adjacency_list_output.txt", "w");
    if (adjacencyListOutput == NULL) {
        printf("Failed to open the adjacency list output file.\n");
        fclose(inputFile);
        return 1;
    }

    FILE* dfsOutput = fopen("dfs_output.txt", "w");
    if (dfsOutput == NULL) {
        printf("Failed to open the DFS output file.\n");
        fclose(inputFile);
        fclose(adjacencyListOutput);
        return 1;
    }

    FILE* bfsOutput = fopen("bfs_output.txt", "w");
    if (bfsOutput == NULL) {
        printf("Failed to open the BFS output file.\n");
        fclose(inputFile);
        fclose(adjacencyListOutput);
        fclose(dfsOutput);
        return 1;
    }

    int numVertices, numEdges;
    fscanf(inputFile, "%d %d", &numVertices, &numEdges);

    AdjList adjList;
    int i;
    for (i = 1; i <= numVertices; ++i) {
        adjList[i].head = NULL;
    }

    int src, dest;
    for (i = 1; i <= numEdges; ++i) {
        fscanf(inputFile, "%d %d", &src, &dest);
        addEdge(adjList, src, dest);
    }

    printAdjacencyList(adjList, numVertices, adjacencyListOutput);
    DFS(adjList, numVertices, dfsOutput);
    BFS(adjList, numVertices, bfsOutput);

    fclose(inputFile);
    fclose(adjacencyListOutput);
    fclose(dfsOutput);
    fclose(bfsOutput);

    freeAdjacencyList(adjList, numVertices);

    printf("Adjacency list, DFS, and BFS outputs generated successfully.\n");

    return 0;
}
