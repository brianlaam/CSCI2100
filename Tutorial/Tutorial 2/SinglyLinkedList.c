#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
    int data;
    struct listNode* link;
}listNode;

typedef struct llist {
    listNode* head;
}llist;

listNode* last(llist* list);

void display(llist* L);

llist* initialize();

listNode* search(int searchnum, llist* list);

void prepend(int data, llist* list);

void append(int data, llist* list);

void deleteFront(llist* list);

void insertInPlace(int data, llist* list, listNode* prev);

void deleteInPlace(llist* list, listNode* prev);

int main() {
    printf("Initialize SinglyLinkedList: \n");
    //Create LinkedList
    llist* list = initialize();

    //Display the current LinkedList
    display(list);

    //Insert three elements 1, 2, 3 to the LinkedList
    prepend(1, list);
    prepend(2, list);
    append(3, list);


    printf("After three elements insertion:\n");

    display(list);

    printf("After the deletion of the front:\n");
    deleteFront(list);
    //Select the position of the element to be deleted
    // listNode* deletion_node = ListSearch(L, 2);
    //Delete the element of the given address from the LinkedList
    // delete(L, deletion_node);
    display(list);


    printf("Insert element right after the first '1' element嚗䨵n");
    //Select the position of the element which is right before the element to be inserted
    listNode* prevNode = search(1, list);
    //insert the element after the selected address(position)
    insertInPlace(7, list, prevNode);
    display(list);

    printf("Delete element right after the first '7' element嚗䨵n");
    prevNode = search(7, list);
    //delete the element after the selected address(position)
    deleteInPlace(list, prevNode);
    display(list);
    return 0;
}

//Create the initial LinkedList with only head node and tail node
llist* initialize()
{
    //Allocate memory for list L
    llist* list1ptr = (llist*)malloc(sizeof(llist));
    list1ptr->head = NULL;
    return list1ptr;
}

//Search a linkedList to return the node of the element we are searching for
listNode* search(int searchnum, llist* list)
{
    listNode* node = list->head;
    while (node != NULL)
    {
        if (node->data == searchnum)
        {
            return node;
        }
        node = node->link;
    }
    return NULL;
}

//Insert an element 'data' at the head of the SinglyLinkedList
void prepend(int data, llist* list)
{
    listNode* temp = (listNode*)malloc(1 * sizeof(listNode));
    temp->data = data;
    if (list->head == NULL)
    {
        temp->link = NULL;
        list->head = temp;
        return;
    }
    temp->link = list->head;
    list->head = temp;
    return;
}

//Insert an element 'data' at the tail of the SinglyLinkedList
void append(int data, llist* list)
{
    if (list->head == NULL)
    {
        prepend(data, list);
        return;
    }
    listNode* lastNode = last(list);
    listNode* temp = (listNode*)malloc(1 * sizeof(listNode*));
    temp->data = data;
    temp->link = NULL;
    lastNode->link = temp;
}

void deleteFront(llist* list)
{
    if (list->head == NULL)
    {
        return;
    }
    listNode* temp = list->head;
    list->head = temp->link;
    free(temp);
    return;
}

listNode* last(llist* list)
{
    listNode* node = list->head;
    if (node == NULL)
    {
        return NULL;
    }
    listNode* next = list->head->link;
    while (next != NULL)
    {
        node = next;
        next = next->link;
    }
    return node;
}

//Display each element in the SinglyLinkedList
void display(llist* L) {
    printf("List: ");
    listNode* temp = L->head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

void insertInPlace(int data, llist* list, listNode* prev)
{
    //Node unew < -allocate a new node from memory
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->data = data;
    newNode->link = prev->link;
    prev->link = newNode;
}

void deleteInPlace(llist* list, listNode* prev)
{
    listNode* lnode = prev->link;
    if (lnode == NULL)
    {
        return;
    }
    prev->link = lnode->link;
    free(lnode);
}