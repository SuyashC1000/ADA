#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

typedef struct AdjListGraph {
  int numVertices;
  Node *adjLists[MAX_VERTICES];
  int visited[MAX_VERTICES];
} AdjListGraph;

typedef struct AdjMatGraph {
  int numVertices;
  int adjMatrix[MAX_VERTICES][MAX_VERTICES];
  int visited[MAX_VERTICES];
} AdjMatGraph;

typedef struct Queue {
  int items[MAX_VERTICES];
  int front;
  int rear;
} Queue;

AdjListGraph *createAdjListGraph(int vertices) {
  AdjListGraph *graph = (AdjListGraph *)malloc(sizeof(AdjListGraph));
  graph->numVertices = vertices;

  for (int i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

AdjMatGraph *createAdjMatGraph(int vertices) {
  AdjMatGraph *graph = (AdjMatGraph *)malloc(sizeof(AdjMatGraph));
  graph->numVertices = vertices;

  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < vertices; j++) {
      graph->adjMatrix[i][j] = 0;
    }
    graph->visited[i] = 0;
  }

  return graph;
}

Queue *createQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isQueueEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, int value) {
  if (q->rear == MAX_VERTICES - 1) {
    return;
  }
  if (isQueueEmpty(q)) {
    q->front = 0;
  }
  q->rear++;
  q->items[q->rear] = value;
}

int dequeue(Queue *q) {
  if (isQueueEmpty(q)) {
    return -1;
  }
  int item = q->items[q->front];
  q->front++;
  if (q->front > q->rear) {
    q->front = q->rear = -1;
  }
  return item;
}

void addAdjListEdge(AdjListGraph *graph, int src, int dest) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = dest;
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = (Node *)malloc(sizeof(Node));
  newNode->vertex = src;
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

void addAdjMatEdge(AdjMatGraph *graph, int src, int dest) {
  graph->adjMatrix[src][dest] = 1;
  graph->adjMatrix[dest][src] = 1;
}

void printAdjListGraph(AdjListGraph *graph) {
  for (int i = 0; i < graph->numVertices; i++) {
    printf("%d -> [", i);
    Node *temp = graph->adjLists[i];
    while (temp != NULL) {
      printf("%d,", temp->vertex);
      temp = temp->next;
    }
    printf("]\n");
  }
}

void printAdjMatGraph(AdjMatGraph *graph) {
  int n = graph->numVertices;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", graph->adjMatrix[i][j]);
    }
    printf("\n");
  }
}

void bfs(AdjListGraph *graph, int startVertex) {
  for (int i = 0; i < graph->numVertices; i++) {
    graph->visited[i] = 0;
  }

  Queue *q = createQueue();
  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isQueueEmpty(q)) {
    int currentVertex = dequeue(q);
    printf("%d ", currentVertex);

    Node *temp = graph->adjLists[currentVertex];
    while (temp) {
      int adjVertex = temp->vertex;
      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
}

void dfs(struct AdjListGraph *graph, int startVertex) {
  Node *adjList = graph->adjLists[startVertex];
  Node *temp = adjList;
  graph->visited[startVertex] = 1;

  printf("%d ", startVertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;

    if (graph->visited[connectedVertex] == 0) {
      dfs(graph, connectedVertex);
    }
    temp = temp->next;
  }
}

void initAdjListGraph(AdjListGraph *graph) {
  addAdjListEdge(graph, 0, 1);
  addAdjListEdge(graph, 0, 2);
  addAdjListEdge(graph, 1, 3);
  addAdjListEdge(graph, 1, 4);
  addAdjListEdge(graph, 2, 5);
}

void initAdjMatGraph(AdjMatGraph *graph) {
  addAdjMatEdge(graph, 0, 1);
  addAdjMatEdge(graph, 0, 2);
  addAdjMatEdge(graph, 1, 3);
  addAdjMatEdge(graph, 1, 4);
  addAdjMatEdge(graph, 2, 5);
}

int main() {
  int vertices = 6;
  AdjListGraph *graph = createAdjListGraph(vertices);
  initAdjListGraph(graph);

  AdjMatGraph *graph2 = createAdjMatGraph(vertices);
  initAdjMatGraph(graph2);

  printAdjListGraph(graph);
  printf("\n");
  printAdjMatGraph(graph2);
  printf("\n");

  for (int i = 0; i < graph->numVertices; i++) {
    graph->visited[i] = 0;
  }
  printf("Breadth first search starting from vertex 0:\n");
  bfs(graph, 0);
  printf("\n");
  for (int i = 0; i < graph->numVertices; i++) {
    graph->visited[i] = 0;
  }
  printf("Depth first search starting from vertex 0:\n");
  dfs(graph, 0);
  printf("\n");
}