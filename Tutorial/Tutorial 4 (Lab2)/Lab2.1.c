#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF -1

typedef enum {PUSH = 1, POP, IS_FULL, IS_EMPTY, TOP, ERROR_OP} OP;

// data structure of the stack, which is implemented by an array "arr"
struct stack {
    int capacity;
    int size;
    int* arr;
};

typedef struct stack* StackADT;

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
// Usage: int result = IsEmpty(yourStack);
int IsEmpty(StackADT s) {
    return s->size == 0;
}

// Description: Return 1 if the stack is full, and 0 otherwise
// Usage: int result = IsFull(yourStack);
int IsFull(StackADT s) {
    return s->size == s->capacity;
}

// Description: Push a value into the stack
// Usage: Push(yourStack, value);
// Tips: If it is full, do nothing.
void Push(StackADT s, int value) {
    if (IsFull(s)) {
        return; 
    }
    s->arr[s->size] = value; // Add the value to the top of the stack
    s->size++; // Increment the size of the stack
}


// Description: Pop a value from the stack
// Usage: Pop(yourStack);
// Tips: If it is empty, do nothing.
void Pop(StackADT s) {
    if (IsEmpty(s)) {
        return;
    }
    s->size--; // Decrement the size of the stack to remove the top element
}

// Description: Obtain the top value from the stack
// Usage: int topValue = Top(yourStack);
// Tips: Your should check if it is empty. If empty, you should return INF.
int Top(StackADT s) {
   if (IsEmpty(s)) {
        return INF; // If the stack is empty, return INF
    }
    return s->arr[s->size - 1]; // Return the top element of the stack
}

// Description: Input management
OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "push") == 0) {
        return PUSH;
    } else if (strcmp(str, "pop") == 0) {
        return POP;
    } else if (strcmp(str, "isFull") == 0) {
        return IS_FULL;
    } else if (strcmp(str, "isEmpty") == 0) {
        return IS_EMPTY;
    } else if (strcmp(str, "top") == 0) {
        return TOP;
    } else {
        return ERROR_OP;
    }
}

int main() {
    int capacity;
    scanf("%d", &capacity);

    // create a stack
    // For example, if you push 2,3,4 into the stack, you actually add these values into "arr" of the stack
    // "arr" of the stack looks like [2, 3, 4]
    StackADT s = CreateStack(capacity);

    int n;
    scanf("%d", &n);

    int op, value;
    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case PUSH:
                scanf(" %d", &value);
                if (IsFull(s)) {
                    printf("Full!!!!\n");
                } else {
                    Push(s, value);
                }
                break;
            case POP:
                Pop(s);
                break;
            case IS_FULL:
                if (IsFull(s)) {
                    printf("Full!!!!\n");
                } else {
                    printf("Not Full\n");
                }
                break;
            case IS_EMPTY:
                if (IsEmpty(s)) {
                    printf("Empty!!!\n");
                } else {
                    printf("Not Empty\n");
                }
                break;
            case TOP:
                if (!IsEmpty(s)) {
                    printf("%d\n", Top(s));
                } else {
                    printf("Empty!!!\n");
                }
                break;
            default:
                printf("Error Input\n");
        }
    }

    return 0;
}
