#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF -1

typedef enum {ENQUEUE = 1, DEQUEUE, IS_FULL, IS_EMPTY, ERROR_OP} OP;

// data structure of the stack, which is implemented by an array "arr"
struct stack {
    int capacity;
    int size;
    int* arr;
};

typedef struct stack* StackADT;

// data structure of the queue, which is implemented by two stacks
struct queue {
    int capacity;
    int size;
    StackADT s1;
    StackADT s2;
};

typedef struct queue* QueueADT;

// Description: Create a stack with the capacity xxx
// Usage: StackADT yourStack = CreateStack(capacity)
StackADT CreateStack(int capacity) {
    StackADT s = (StackADT) malloc(sizeof(struct stack));
    s->arr = (int*) malloc(capacity * sizeof(int));
    s->capacity = capacity;
    s->size = 0;
    return s;
}

// Description: Return 1 if the stack is empty, and 0 otherwise
// Usage: int result = IsStackEmpty(yourStack);
int IsStackEmpty(StackADT s) {
    return s->size == 0;
}

// Description: Return 1 if the stack is full, and 0 otherwise
// Usage: int result = IsStackFull(yourStack);
int IsStackFull(StackADT s) {
    return s->size == s->capacity;
}

// Description: Push a value into the stack
// Usage: Push(yourStack, value);
// Tips: If it is full, do nothing.
void Push(StackADT s, int value) {
    if (IsStackFull(s)) {
        return; 
    }
    s->arr[s->size] = value;
    s->size++; 
}

// Description: Pop a value from the stack
// Usage: Pop(yourStack);
// Tips: If it is empty, do nothing.
void Pop(StackADT s) {
    if (IsStackEmpty(s)) {
        return; 
    }
    s->size--; 
}

// Description: Obtain the top value from the stack
// Usage: int topValue = Top(yourStack);
// Tips: Your should check if it is empty. If empty, you should return INF.
int Top(StackADT s) {
    if (IsStackEmpty(s)) {
        return INF; 
    }
    return s->arr[s->size - 1]; 
}

// Description: Create a queue with the capacity xxx
// Usage: QueueADT yourQueue = CreateQueue(capacity)
QueueADT CreateQueue(int capacity) {
    QueueADT q = (QueueADT) malloc(sizeof(struct queue));
    q->s1 = CreateStack(capacity);
    q->s2 = CreateStack(capacity);
    q->capacity = capacity;
    q->size = 0;
    return q;
}

// Description: Return 1 if the queue is empty, and 0 otherwise
// Usage: int result = IsQueueEmpty(yourQueue);
int IsQueueEmpty(QueueADT q) {
    return q->size == 0;
}

// Description: Return 1 if the queue is full, and 0 otherwise
// Usage: int result = IsQueueFull(yourQueue);
int IsQueueFull(QueueADT q) {
    return q->size == q->capacity;
}

// Description: Enqueue a value into the queue
// Usage: Enqueue(yourQueue, value);
// Tips: You should check if it is full
void Enqueue(QueueADT q, int value) {
    if (IsQueueFull(q)) {
        return; 
    }
    Push(q->s1, value); 
    q->size++; 
}

// Description: Dequeue an item from the queue
// Usage: int result = Dequeue(yourQueue);
// Tips: If it is empty, you should return INF. Otherwise, return the value of the item.
int Dequeue(QueueADT q) {
    if (IsQueueEmpty(q)) {
        printf("Empty!!!!\n");
        return INF;
    }
    if (IsStackEmpty(q->s2)) {
        // If the second stack is empty, transfer elements from the first stack
        while (!IsStackEmpty(q->s1)) {
            Push(q->s2, Top(q->s1)); // Push elements from the first stack to the second stack
            Pop(q->s1); // Pop elements from the first stack
        }
    }
    int value = Top(q->s2); // Get the front element from the second stack
    Pop(q->s2); // Pop the front element from the second stack
    q->size--; // Decrement the size of the queue
    return value; // Return the dequeued value
}

// Description: Input management
OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "enqueue") == 0) {
        return ENQUEUE;
    } else if (strcmp(str, "dequeue") == 0) {
        return DEQUEUE;
    } else if (strcmp(str, "isFull") == 0) {
        return IS_FULL;
    } else if (strcmp(str, "isEmpty") == 0) {
        return IS_EMPTY;
    } else {
        return ERROR_OP;
    }
}

int main() {
    int capacity;
    scanf("%d", &capacity);

    // create a queue
    // For example, if you push 2,3,4 into the queue, you add them into the linked list.
    // The linked list looks like "head <-> 2 <-> 3 <-> 4 <-> tail"
    QueueADT q = CreateQueue(capacity);

    int n;
    scanf("%d", &n);

    int op, value;
    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case ENQUEUE:
                scanf(" %d", &value);
                if (IsQueueFull(q)) {
                    printf("Full!!!!\n");
                } else {
                    Enqueue(q, value);
                }
                break;
            case DEQUEUE:
                if (IsQueueEmpty(q)) {
                    printf("Empty!!!!\n");
                } else {
                    printf("%d\n", Dequeue(q));
                }
                break;
            case IS_FULL:
                if (IsQueueFull(q)) {
                    printf("Full!!!!\n");
                } else {
                    printf("Not Full\n");
                }
                break;
            case IS_EMPTY:
                if (IsQueueEmpty(q)) {
                    printf("Empty!!!!\n");
                } else {
                    printf("Not Empty\n");
                }
                break;
            default:
                printf("Error Input\n");
        }
    }

    return 0;
}