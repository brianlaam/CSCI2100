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

typedef enum {PUT = 1, GET, ERASE, SIZE, ERROR_OP} OP;

const int hashTableSize = 29989;

// this linked list has no head or tail, which means that if this list is empty, then it equals NULL
struct linkedList {
    int key;
    int value;
    struct linkedList* next;
};

typedef struct linkedList* ListNode;

struct map {
    int size;
    ListNode* hashTable;
};

typedef struct map* MapADT;

int HashFunction(int key) {
    return key % hashTableSize;
}

// linked list
ListNode CreateNode(int key, int value) {
    ListNode node = (ListNode) malloc(sizeof(struct linkedList));
    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;
}

// Map

// Initially, each linked list in the hashTable is NULL 
// Hashing collision resolution: chaining
MapADT CreateMap() {
    MapADT m = (MapADT) malloc(sizeof(struct map));
    m->size = 0;
    m->hashTable = (ListNode*) malloc(hashTableSize * sizeof(ListNode));
    memset(m->hashTable, 0, hashTableSize * sizeof(ListNode)); 

    return m;
}

int Size(MapADT myMap) {
    return myMap->size;
}

void Put(MapADT myMap, int key, int value) {
    int index = HashFunction(key);
    ListNode currentNode = myMap->hashTable[index];
    ListNode prevNode = NULL;

    // Update the key value if it exists
    while (currentNode != NULL) {
        if (currentNode->key == key) {
            currentNode->value = value;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // Create a new node and insert to the beginning if the key is not found
    ListNode newNode = CreateNode(key, value);
    if (prevNode != NULL) {
        prevNode->next = newNode;
    } else {
        myMap->hashTable[index] = newNode;
    }
    myMap->size++;
}

int Get(MapADT myMap, int key) {
    int index = HashFunction(key);
    ListNode currentNode = myMap->hashTable[index];

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }

    return INF;
}

void Erase(MapADT myMap, int key) {
    int index = HashFunction(key);
    ListNode currentNode = myMap->hashTable[index];
    ListNode prevNode = NULL;

    while (currentNode != NULL) {
        if (currentNode->key == key) {
            if (prevNode != NULL) {
                prevNode->next = currentNode->next;
            } else {
                myMap->hashTable[index] = currentNode->next;
            }
            free(currentNode);
            myMap->size--;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "put") == 0) {
        return PUT;
    } else if (strcmp(str, "get") == 0) {
        return GET;
    } else if (strcmp(str, "erase") == 0) {
        return ERASE;
    } else if (strcmp(str, "size") == 0) {
        return SIZE;
    } else {
        return ERROR_OP;
    }
}

int main() {
    int n, key, value;
    MapADT myMap = CreateMap();
    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case PUT:
                scanf(" %d%d", &key, &value);
                Put(myMap, key, value);
                break;
            case GET:
                scanf(" %d", &key);
                printf("%d\n", Get(myMap, key));
                break;
            case ERASE:
                scanf(" %d", &key);
                Erase(myMap, key);
                break;
            case SIZE:
                printf("%d\n", Size(myMap));
                break;
            default:
                printf("Error Input\n");
        }
    }
}


