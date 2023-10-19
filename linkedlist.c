#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"
#include <string.h>

linkedlist_t* InitLinkedList()
{
    linkedlist_t* list = (linkedlist_t*)calloc(1, sizeof(linkedlist_t));
    return list;
}


void* removeFirst(linkedlist_t* list)
{
    if (list->count == 0)
    {
        return NULL;
    }
    else
    {
        node_t* tempNode;
        void* item;

        tempNode = list->head;
        list->head = list->head->next;

        list->count = list->count - 1;
        item = tempNode->value;

        free(tempNode);
        return item;
    }
}

void* removeLast(linkedlist_t* list)
{
    if (list->count == 0)
    {
        return NULL;
    }
    else
    {
        node_t* tempNode;
        void* item;

        tempNode = list->tail;
        list->tail = tempNode->previous;
        
        list->count = list->count - 1;
        item = tempNode->value;

        free(tempNode);
        return item;
    }
}

void InsertFirst(linkedlist_t* list, void* value, int valueSize)
{
    node_t* newNode = (node_t*)calloc(1, sizeof(node_t));
    
    if (list->count == 0)
    {
        list->tail = newNode;
        list->head = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->previous = newNode;
        list->head = newNode;
    }
    
    /* value Copying */
    newNode->value = malloc(valueSize);
    list->count = list->count + 1;
    
    memcpy(newNode->value, value, valueSize);
}

void InsertLast(linkedlist_t* list, void* value, int valueSize)
{
    node_t* newNode = (node_t*)calloc(1, sizeof(node_t));

    if (list->count == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->previous = list->tail;
        list->tail = newNode;
    }

    /* value Copying */
    newNode->value = malloc(valueSize);
    list->count = list->count + 1;
    
    memcpy(newNode->value, value, valueSize);
}

void freeLinkedList(linkedlist_t* list)
{
    node_t *current, *nextNode;

    current = list->head;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current->value);
        free(current);
        current = nextNode;
    }
    
    free(list);
}