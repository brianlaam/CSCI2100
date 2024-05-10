#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF -1

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
    s->arr[s->size++] = value;   
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
        return INF; 
    }
    return s->arr[s->size - 1]; // Return the top element of the stack    
}

// Description: Calculate the number of unblocked buildings that a new item can see
// Usage: int numOfBuildings = DoSomething(yourStack, newValue);
// Tips: Implement it with the stack. 
// Tips: You may push every item into the stack. 
// Tips: Before you push a new item into the stack, you may do something in order to maintain certain property of this stack.
// Tips: This property should help a new item calculate the number of unblocked buildings it can see.
int DoSomething(StackADT s, int value) {
    int visibleBuildings = 0;
    visibleBuildings = s->size;        

    while (!IsEmpty(s) && s->arr[s->size - 1] <= value) {
        Pop(s);
    }

    Push(s, value); 
    return visibleBuildings;
}

int main() {
    int n;
    scanf("%d", &n);
    StackADT s = CreateStack(n);

    int value;
    for(int i=0; i<n; i++) {
        scanf("%d", &value);
        printf("%d\n", DoSomething(s, value));
    }
}