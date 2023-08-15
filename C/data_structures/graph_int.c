#include <stdio.h>
#include <stdlib.h>

#include "queue_list_int.c"

#define MAX_SIZE 16

typedef struct AdjListNode AdjListNode;
struct AdjListNode
{
    int value;
    AdjListNode *next;
};

typedef struct Graph
{
    AdjListNode *items[MAX_SIZE];
    char visited[MAX_SIZE];
} Graph;

Graph *createGraph()
{
    Graph *graph = malloc(sizeof(Graph));
    for (int i = 0; i < MAX_SIZE; i++)
    {
        graph->items[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

AdjListNode *createAdjListNode(int value)
{
    AdjListNode *node = malloc(sizeof(AdjListNode));
    node->next = NULL;
    node->value = value;
    return node;
}

/**
 * @brief Add vertex to undirected graph.
 *
 * @param graph
 * @param vertex1
 * @param vertex2
 */
void addEdge(Graph *graph, int vertex1, int vertex2)
{
    AdjListNode *vertex = createAdjListNode(vertex2);
    vertex->next = graph->items[vertex1];
    graph->items[vertex1] = vertex;

    vertex = createAdjListNode(vertex1);
    vertex->next = graph->items[vertex2];
    graph->items[vertex2] = vertex;
}

void _dfs(Graph *graph, int source)
{
    graph->visited[source] = 1;
    printf("%d ", source);
    AdjListNode *current = graph->items[source];

    while (current != NULL)
    {
        if (graph->visited[current->value] == 0)
        {
            _dfs(graph, current->value);
        }
        current = current->next;
    }
}

void dfs(Graph *graph)
{
    int source;
    for (source = 0; source < MAX_SIZE; source++)
    {
        if (graph->items[source] != NULL)
        {
            break;
        }
    }

    if (graph->items[source] == NULL)
    {
        printf("Graph is empty.\n");
        return;
    }

    _dfs(graph, source);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        graph->visited[i] = 0;
    }
    printf("\n");
}

void bfs(Graph *graph)
{
    int source;
    for (source = 0; source < MAX_SIZE; source++)
    {
        if (graph->items[source] != NULL)
        {
            break;
        }
    }

    if (graph->items[source] == NULL)
    {
        printf("Graph is empty.\n");
        return;
    }

    QueueList *q = createQueueList();

    graph->visited[source] = 1;
    enqueue(q, source);
    printf("%d ", source);

    while (!isEmpty(q))
    {
        int currentSource = dequeue(q);
        AdjListNode *current = graph->items[currentSource];
        while (current != NULL)
        {
            if (graph->visited[current->value] == 0)
            {
                printf("%d ", current->value);
                graph->visited[current->value] = 1;
                enqueue(q, current->value);
            }
            current = current->next;
        }
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        graph->visited[i] = 0;
    }
    printf("\n");
}

int main(void)
{
    Graph *graph = createGraph();

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 3);

    dfs(graph);
    bfs(graph);
    return 0;
}