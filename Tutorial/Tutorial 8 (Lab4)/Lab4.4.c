/*
I, Lam Hoi Chun, am submitting the assignment for
an individual project.
I declare that the assignment here submitted is original except for
source material explicitly acknowledged, the piece of work, or a part
of the piece of work has not been submitted for more than one purpose
(i.e. to satisfy the requirements in two different courses) without
declaration. I also acknowledge that I am aware of University policy
and regulations on honesty in academic work, and of the disciplinary
guidelines and procedures applicable to breaches of such policy and
regulations, as contained in the University website
http://www.cuhk.edu.hk/policy/academichonesty/.
It is also understood that assignments without a properly signed
declaration by the student concerned will not be graded by the
teacher(s).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_DISTANCE 999999
#define MAX_NODES 1000
#define CAPACITY 4000

// min heap
struct node {
    int id;
    int dis;
};

typedef struct node* Node;

struct Heap {
    int capacity;
    int size;
    Node* arr;
};

typedef struct Heap* HeapADT;

Node CreateNode(int id, int dis) {
    Node tmp = (Node) malloc(sizeof(struct node));
    tmp->id = id;
    tmp->dis = dis;
    return tmp;
}

HeapADT CreateHeap(int capacity) {
    HeapADT heap = (HeapADT) malloc(sizeof(struct Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (Node*) malloc((capacity + 1) * sizeof(struct node));

    return heap;
}

void InsertHeap(HeapADT heap, Node tmp) {
    if (heap->size < heap->capacity) {
        heap->size++;

        int cur = heap->size;
        int father = cur / 2;
        while (father >= 1 && heap->arr[father]->dis > tmp->dis) {
            heap->arr[cur] = heap->arr[father];
            cur = father;
            father = cur / 2;
        }

        heap->arr[cur] = tmp;
    }
}

void DeleteHeap(HeapADT heap) {
    if (heap->size != 0) {
        Node tmp = heap->arr[heap->size];
        heap->size--;

        int cur = 1;
        int child = cur * 2;

        while (child <= heap->size) {
            if (child + 1 <= heap->size && heap->arr[child+1]->dis < heap->arr[child]->dis) {
                child++;
            }

            if (heap->arr[child]->dis < tmp->dis) {
                heap->arr[cur] = heap->arr[child];
                cur = child;
                child = cur * 2;
            } else {
                break;
            }
        }

        heap->arr[cur] = tmp;
    }
}

Node Top(HeapADT heap) {
    if (heap->size > 0) {
        return heap->arr[1];
    } else {
        return NULL;
    }
}

int Empty(HeapADT heap) {
    if (heap->size > 0) {
        return 0;
    } else {
        return 1;
    }
}

// graph related data structure
struct edgeNode {
    int v;
    int weight;
};

typedef struct edgeNode Edge;

// the maximum number of nodes is known as MAX_NODES
// we use array to store every edge, represented by Edge
// For example, graph[1][2] is the third neighbor of the node 1. Its id is graph[1][2].v and its edge weight is graph[1][2].weight
// we use edgeNum to record the number of neighbors of each node
// For example, edgeNum[1] is the number of edges of the node 1
Edge graph[MAX_NODES][MAX_NODES];
int edgeNum[MAX_NODES];

int dist[MAX_NODES];
int color[MAX_NODES];
HeapADT myHeap; // min heap

// Tips: use the HeapADT & Try to stop early
int CloseNeighbor(int src, int n, int k) {
    Reset(); 

    dist[src] = 0;
    InsertHeap(myHeap, CreateNode(src, 0));

    while (!Empty(myHeap)) {
        Node current = Top(myHeap);
        DeleteHeap(myHeap);

        if (current->dis > k)
            break;

        int u = current->id;

        for (int i = 0; i < edgeNum[u]; ++i) {
            int v = graph[u][i].v;
            int weight = graph[u][i].weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                InsertHeap(myHeap, CreateNode(v, dist[v]));
            }
        }
    }

    int closeNeighbors = 0;
    for (int i = 1; i <= n; ++i) {
        if (i != src && dist[i] <= k)
            closeNeighbors++;
    }

    return closeNeighbors;
}

void Reset() {
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = MAX_DISTANCE;
        color[i] = 0;
    }

    myHeap->size = 0;
}

int main() {
	for (int i = 0; i < MAX_NODES; i++) {
        edgeNum[i] = 0;
	}

    myHeap = CreateHeap(CAPACITY);
	
	int n, m, src, k;
	scanf("%d%d%d",&n, &m, &k);
	
	int x, y, w;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &x, &y, &w);
        graph[x][edgeNum[x]].v = y;
        graph[x][edgeNum[x]++].weight = w;
        graph[y][edgeNum[y]].v = x;
        graph[y][edgeNum[y]++].weight = w;
	}

    int num;
    scanf("%d", &num);

    for (int i=0;i<num;++i) {
        scanf("%d", &src);
        Reset();
        printf("%d\n", CloseNeighbor(src, n, k));
    }
	
	return 0;
}