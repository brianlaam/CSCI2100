#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF -1

typedef enum {ENQUEUE = 1, DEQUEUE, IS_FULL, IS_EMPTY, ERROR_OP} OP;

// data structure of each node in the queue
// Tips: each node is actually a linked list node
struct queueNode {
    int value;
    struct queueNode* next;
    struct queueNode* prev;
};

typedef struct queueNode* QueueNode;

// data structure of the queue
struct queue {
    int capacity;
    int size;
    QueueNode head;
    QueueNode tail;
};

typedef struct queue* QueueADT;

// Description: Create a queue node
// Usage: QueueNode newNode = AllocateEmptyQueueNode()
QueueNode AllocateEmptyQueueNode() {
    QueueNode newNode = (QueueNode) malloc(sizeof(struct queueNode));
    newNode->value = INF;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Description: Create a queue with the capacity xxx
// Usage: QueueADT yourQueue = CreateQueue(capacity)
// Tips: It has two dummy nodes: "head" and "tail"
QueueADT CreateQueue(int capacity) {
    QueueADT q = (QueueADT) malloc(sizeof(struct queue));
    q->capacity = capacity;
    q->size = 0;
    q->head = AllocateEmptyQueueNode();
    q->tail = AllocateEmptyQueueNode();
    q->head->next = q->tail;
    q->tail->prev = q->head;
    return q;
}

// Description: Return 1 if the queue is empty, and 0 otherwise
// Usage: int result = IsEmpty(yourQueue);
int IsEmpty(QueueADT q) {
    return q->size == 0;
}

// Description: Return 1 if the queue is full, and 0 otherwise
// Usage: int result = IsFull(yourQueue);
int IsFull(QueueADT q) {
    return q->size == q->capacity;
}

// Description: Enqueue a value into the queue
// Usage: Enqueue(yourQueue, value);
// Tips: You should check if it is full
void Enqueue(QueueADT q, int value) {
    if (IsFull(q)) {
        printf("Full!!!!\n");
        return;
    }
    QueueNode newNode = AllocateEmptyQueueNode(); 
    newNode->value = value; 
    newNode->prev = q->tail->prev; 
    newNode->next = q->tail; 
    q->tail->prev->next = newNode; 
    q->tail->prev = newNode; 
    q->size++; 
}

// Description: Dequeue an item from the queue
// Usage: int result = Dequeue(yourQueue);
// Tips: If it is empty, you should return INF. Otherwise, return the value of the item.
int Dequeue(QueueADT q) {
   if (IsEmpty(q)) {
        printf("Empty!!!!\n");
        return INF; 
    }
    QueueNode frontNode = q->head->next;
    int value = frontNode->value;
    q->head->next = frontNode->next; 
    frontNode->next->prev = q->head; 
    free(frontNode); 
    q->size--;
    return value;
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
                if (IsFull(q)) {
                    printf("Full!!!!\n");
                } else {
                    Enqueue(q, value);
                }
                break;
            case DEQUEUE:
                if (IsEmpty(q)) {
                    printf("Empty!!!!\n");
                } else {
                    printf("%d\n", Dequeue(q));
                }
                break;
            case IS_FULL:
                if (IsFull(q)) {
                    printf("Full!!!!\n");
                } else {
                    printf("Not Full\n");
                }
                break;
            case IS_EMPTY:
                if (IsEmpty(q)) {
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
