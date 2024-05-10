#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
    int element;
    struct listNode* prev;
    struct listNode* next;
}listNode;

typedef struct llist {
    listNode* head;
	listNode* tail;
}llist;

llist* createList();

listNode* ListSearch(llist *L, int num);

void insert(llist *L, int e);

void insertInPlace(llist *L, listNode* p, int e);

void delete(llist* L, listNode* p);

void display(llist* L);

int main() {
    printf("Initialize LinkedList: \n");
    // Create LinkedList
    llist *L = createList();
    
    //Display the current LinkedList
    display(L);
    
    // Insert three elements 2, 3, 5 to LinkedList
    insert(L, 2);
    printf("After the insertion of 2:\n");
    display(L);
    
    insert(L, 3);
    printf("After the insertion of 3:\n");
    display(L);

    insert(L, 5);
    printf("After the insertion of 5:\n");
    display(L);

    printf("Delete element 3\n");
    // Find the position of the element to be deleted
    listNode* deletion_node = ListSearch(L, 3);
    delete(L, deletion_node);
    display(L);

    printf("Insert element right after the first '2' element: \n");
    //Select the position of the element which is right before the element to be inserted
    listNode* prev_node = ListSearch(L, 2);
    //insert the element after the selected address(position)
    insertInPlace(L, prev_node, 7);
    display(L);

    return 0;
}

//Create the initial linked list with only head node and tail node
llist* createList() 
{
    // Allocate memory for List L, Nodes L.head and L.tail		
    llist* L = (llist*)malloc(sizeof(llist));
	listNode* head = (listNode*)malloc(sizeof(listNode));
	listNode* tail = (listNode*)malloc(sizeof(listNode));
	// Update each element
	L->head = head;
    L->tail = tail;	
    L->head->prev = NULL;
    L->head->next = L->tail;
    L->tail->prev = L->head;
    L->tail->next = NULL;
    L->head->element = -1;
    L->tail->element = -1;
	return L;
}

//Search a linked List to return the node of the element we are searching for
listNode* ListSearch(llist *L, int num) 
{
	listNode * node = L->head->next;
    while (node != L->tail) {
        if (node->element == num) {
		    return node;
        }
		node = node->next;
	}
	return NULL;
}

// Insert a node with Element e at the end of the linked list
void insert(llist *L, int e) 
{
    listNode* ulast = L->tail->prev;
    // Allocate a new node from memory
    listNode* unew = (listNode*)malloc(sizeof(listNode));
    unew->element = e;
    unew->prev = ulast;
    unew->next = L->tail;
    ulast->next = unew;
    L->tail->prev = unew;
}

//Insert a node after Node p with Element e
void insertInPlace(llist *L, listNode* p, int e) 
{
    //Allocate a new node from memory
    listNode* unew = (listNode*)malloc(sizeof(listNode));
    unew->element = e;
    unew->prev = p;
    listNode *q = p->next;
    unew->next = q;
    p->next = unew;
    q->prev = unew;
}

// Delete Node p
void delete(llist* L, listNode* p) 
{
    listNode* uprev = p->prev;
    listNode* usucc = p->next;
    uprev->next = usucc;
    usucc->prev = uprev;
    free(p);
}

//Display each element in the linked list
void display(llist* L) 
{
    printf("List: ");
    listNode* temp = L->head;
    while (temp != NULL) {
        if (temp == L->head) {
            printf("head<->");
        }
        else if (temp == L->tail) {
            printf("tail\n");
        }
        else {
            printf("%d<->", temp->element);
        }
        temp = temp->next;
    }
}