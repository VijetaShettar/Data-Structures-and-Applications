#include <stdio.h>
#include <stdbool.h>

#define max_size 100
#define max_vertices 100

typedef struct
{
  int num[max_size];
  int front;
  int rear;
}queue;

void initqueue(queue *q)
{
    q->front=-1;
    q->rear=-1;
}

bool isempty(queue *q)
{
    return q->rear==-1;
}

void enqueue(queue *q,int val)
{
    if(q->rear==max_size-1)
    {
        printf("queue is full\n");
    }
    else
    {
        if(q->front==-1)
        q->front=0;
        q->rear++;
        q->num[q->rear]=val;
    }

}

int dequeue(queue *q)
{
    int num;
    if(isempty(q))
    {
        printf("Queue is empty\n");
    num=-1;
    }
    else{
        num=q->num[q->front];
        q->front++;
        if(q->front>q->rear)
        {
            q->front=q->rear=-1;
        }
    }
    return num;
}

typedef struct
{
    int matrix[max_vertices][max_vertices];
    int numbervertices;
}graph;

 void initgraph(graph *g, int numbervertices)
{
    int i,j;
    g->numbervertices=numbervertices;
    for(i=0;i<numbervertices;i++)
    {
        for(j=0;j<numbervertices;j++)
        {
            g->matrix[i][j]=0;
        }
    }
}

void createedge(graph *g,int src,int dest)
{
    g->matrix[src][dest]=1;
    g->matrix[dest][src]=1;
}

void bfs(graph *g, int vertexsp)
{
    queue q;
    int i;
    bool visited[max_vertices]={false};

    initqueue(&q);

    visited[vertexsp]=true;
    enqueue (&q,vertexsp);

    while(!isempty(&q))
    {
        int curvertex=dequeue(&q);
        printf("%d",curvertex);
    for(i=0;i<=g->numbervertices;i++)
    {
        if(g->matrix[curvertex][i]==1&&!visited[i])
        {
            visited[i]=true;
            enqueue(&q,i);
        }
    }
    }
}

int main()
{
    graph g;
    int i,numbervertices,edges,src,dest;

    printf("enter the number of vertices\n");
    scanf("%d",&numbervertices);
    initgraph(&g,numbervertices);

    printf("enter the number of edges\n");
    scanf("%d",&edges);

    for(i=0;i<edges;i++)
    {
        printf("enter the edge %d(source destination):",i+1);
        scanf("%d%d",&src,&dest);
        createedge(&g,src,dest);
    }
    int vertexsp;
    printf("enter the starting point of vertex for BFS: \n");
    scanf("%d",&vertexsp);

    printf("breadth first traversal: ");
    bfs(&g,vertexsp);
}
