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

    FILE* outputFile = fopen("adjacency_list_output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file.\n");
        fclose(inputFile);
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

    printAdjacencyList(adjList, numVertices, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    freeAdjacencyList(adjList, numVertices);

    printf("Adjacency list generated successfully.\n");

    return 0;
}

