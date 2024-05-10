#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {ADD = 1, DELETE, QUERY, ERROR_OP} OP;

// this linked list has no head or tail, which means that if this list is empty, then it equals NULL
struct linkedListNode {
    int id;
    struct linkedListNode* next;
};

typedef struct linkedListNode* ListNode;

ListNode CreateNode(int id) {
    ListNode node = (ListNode) malloc(sizeof(struct linkedListNode));
    node->id = id;
    node->next = NULL;

    return node;
}

// Stack ADT
struct stack {
    int capacity;
    int* arr;
    int size;
};

typedef struct stack* StackADT;

StackADT CreateStack(int capacity) {
    StackADT s = (StackADT) malloc(sizeof(struct stack));
    s->arr = (int*) malloc(capacity * sizeof(int));
    s->capacity = capacity;
    s->size = 0;
    return s;
}

int IsEmpty(StackADT s) {
    return s->size == 0;
}

void Push(StackADT s, int value) {
    if (s->size < s->capacity) {
        s->arr[s->size++] = value;
    }
}

void Pop(StackADT s) {
    if (!IsEmpty(s)) {
        s->size--;
    }
}

int Top(StackADT s) {
    return s->arr[s->size-1];
}

// graph

// We use array to maintain nodes instead of the hashTables.
// For example, G[i] is exactly the adjacency list of the node i
struct graph {
    int n;
    ListNode* G;
};

typedef struct graph* GraphADT;

GraphADT CreateGraph(int n) {
    GraphADT myGraph = (GraphADT) malloc(sizeof(struct graph));
    myGraph->n = n;
    myGraph->G = (ListNode*) malloc(n * sizeof(ListNode));
    memset(myGraph->G, 0, n * sizeof(ListNode));

    return myGraph;
}

// In our test case, each edge is only added once
void AddEdge(GraphADT myGraph, int u, int v) {
    if (u < 0 || u >= myGraph->n || v < 0 || v >= myGraph->n)
        return; 
    ListNode newNode = CreateNode(v);
    newNode->next = myGraph->G[u];
    myGraph->G[u] = newNode;
}

void DeleteEdge(GraphADT myGraph, int u, int v) {
    if (u < 0 || u >= myGraph->n || v < 0 || v >= myGraph->n)
        return; 

    ListNode current = myGraph->G[u];
    ListNode prev = NULL;

    while (current != NULL) {
        if (current->id == v) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                myGraph->G[u] = current->next;
            }
            free(current);
            return; 
        }
        prev = current;
        current = current->next;
    }
}

int DFS(GraphADT myGraph, int u, int v, int* color) {
    if (u == v)
        return 1; 

    color[u] = 1;

    ListNode current = myGraph->G[u];
    while (current != NULL) {
        if (color[current->id] == 0 && DFS(myGraph, current->id, v, color)) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

// check whether there is path from u to v. If there is a path, return 1. Otherwise, return 0.
// please use DFS
int Query(GraphADT myGraph, int u, int v) {
    int* color = (int*) malloc(myGraph->n * sizeof(int));
    memset(color, 0, myGraph->n * sizeof(int));

    int result = DFS(myGraph, u, v, color);
    free(color);
    return result;
}

OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "add") == 0) {
        return ADD;
    } else if (strcmp(str, "delete") == 0) {
        return DELETE;
    } else if (strcmp(str, "query") == 0) {
        return QUERY;
    } else {
        return ERROR_OP;
    }
}

int main() {
    int n, u, v;
    scanf("%d", &n);
    GraphADT myGraph = CreateGraph(n);

    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case ADD:
                scanf(" %d%d", &u, &v);
                AddEdge(myGraph, u, v);
                break;
            case DELETE:
                scanf(" %d%d", &u, &v);
                DeleteEdge(myGraph, u, v);
                break;
            case QUERY:
                scanf(" %d%d", &u, &v);
                if (Query(myGraph, u, v)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            default:
                printf("Error Input\n");
        }
    }
}
