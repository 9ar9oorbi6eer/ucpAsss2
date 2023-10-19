#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node_t
{
    void* value;
    struct node_t* next;
    struct node_t* previous;
    
} node_t;

typedef struct linkedlist_t
{
    node_t* head;
    node_t* tail;
    int count;

} linkedlist_t;

linkedlist_t* InitLinkedList();
void InsertFirst(linkedlist_t* list, void* value, int valueSize);
void InsertLast(linkedlist_t* list, void* value, int valueSize);
void* removeFirst(linkedlist_t* list);
void* removeLast(linkedlist_t* list);
void freeLinkedList(linkedlist_t* list);


#endif