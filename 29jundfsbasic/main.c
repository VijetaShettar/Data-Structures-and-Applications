#include <stdio.h>
#include <stdbool.h>

#define max_size 100
#define max_vertices 100

typedef struct {
    int num[max_size];
    int top;
} stack;

void initstack(stack *s) {
    s->top = -1;
}

bool isstackempty(stack *s) {
    return s->top == -1;
}

bool isstackfull(stack *s) {
    return s->top == max_size - 1;
}

void push(stack *s, int val) {
    if (isstackfull(s)) {
        printf("Stack is full\n");
    } else {
        s->top++;
        s->num[s->top] = val;
    }
}

int pop(stack *s) {
    int num;
    if (isstackempty(s)) {
        printf("Stack is empty\n");
        num = -1;
    } else {
        num = s->num[s->top];
        s->top--;
    }
    return num;
}

typedef struct {
    int matrix[max_vertices][max_vertices];
    int numbervertices;
} graph;

void initgraph(graph *g, int numbervertices) {
    int i, j;
    g->numbervertices = numbervertices;
    for (i = 0; i < numbervertices; i++) {
        for (j = 0; j < numbervertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

void createedge(graph *g, int src, int dest) {
    g->matrix[src][dest] = 1;
    g->matrix[dest][src] = 1;
}

void dfs(graph *g, int vertexsp) {
    stack s;
    int i;
    bool visited[max_vertices] = {false};

    initstack(&s);

    visited[vertexsp] = true;
    push(&s, vertexsp);

    while (!isstackempty(&s)) {
        int curvertex = pop(&s);
        printf("%c ", curvertex + 'a');

        for (i = 0; i <= g->numbervertices; i++) {
            if (g->matrix[curvertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                push(&s, i);
            }
        }
    }
}

int main() {
    graph g;
    int i, numbervertices, edges;
    char src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &numbervertices);
    initgraph(&g, numbervertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter the edge %d (source destination): ", i + 1);
        scanf(" %c %c", &src, &dest);
        createedge(&g, src - 'a', dest - 'a');
    }

    char vertexsp;
    printf("Enter the starting point of vertex for DFS: ");
    scanf(" %c", &vertexsp);

    printf("Depth-first traversal: ");
    dfs(&g, vertexsp - 'a');
    return 0;
}
