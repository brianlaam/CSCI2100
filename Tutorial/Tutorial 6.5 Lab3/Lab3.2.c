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
#include <string.h>
#define INF -1

typedef enum {INSERT = 1, DELETE, TOP, ERROR_OP} OP;

struct Heap {
    int capacity;
    int size;
    int* arr;
};

typedef struct Heap* HeapADT;

HeapADT Create(int capacity) {
    HeapADT heap = (HeapADT) malloc(sizeof(struct Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (int*) malloc((capacity + 1) * sizeof(int));

    return heap;
}


void InsertHeap(HeapADT heap, int value) {
    if (heap->size >= heap->capacity) // Heap is full
        return; 

    heap->size++;
    int i = heap->size;
    heap->arr[i] = value;

    // Ensure heap property holds
    while (i>1 && heap->arr[i/2] > heap->arr[i]) {
        // Parent node <-> Current node
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[i / 2];
        heap->arr[i / 2] = temp;

        i /= 2; // Update current position: Move to parent
    }    
}

void DeleteHeap(HeapADT heap) {
    if (heap->size == 0) // Heap is empty
        return; 

    // Replace root with last element
    heap->arr[1] = heap->arr[heap->size];
    heap->size--;

    // Ensure heap property holds
    int i = 1;
    while (1) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int smallest = i;

        // Find the smallest child
        if (left <= heap->size && heap->arr[left] < heap->arr[i])
            smallest = left;
        if (right <= heap->size && heap->arr[right] < heap->arr[smallest])
            smallest = right;

        if (smallest == i) // Current node < both children
            break;

        // Current node <-> Smallest child
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = temp;

        i = smallest; // Update current position: Move to smallest child
    }    
}

// Return the smallest value in the heap
// If the heap is empty, return INF
int Top(HeapADT heap) {
    if (heap->size == 0) // Heap is empty
        return INF;
        
    return heap->arr[1];
}

OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "insert") == 0) {
        return INSERT;
    } else if (strcmp(str, "delete") == 0) {
        return DELETE;
    } else if (strcmp(str, "top") == 0) {
        return TOP;
    } else {
        return ERROR_OP;
    }
}

int main() {
    int n, capacity, operation, value;
    scanf("%d%d", &capacity, &n);

    HeapADT heap = Create(capacity);

    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case INSERT:
                scanf("%d", &value);
                InsertHeap(heap, value);
                break;
            case DELETE:
                DeleteHeap(heap);
                break;
            case TOP:
                printf("%d\n", Top(heap));
                break;
            default:
                printf("Error Input\n");
        }
    }
}
