#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void* data;
    struct node* next;
    struct node* prev;
}
node;

typedef struct
{
    node* first;
    node* last;
    node* current;
}
List;



List* createList ();
void pushFront (List*, void*);
void pushBack (List*, void*);
void pushCurrent (List*, void*);
void popFront (List*);
void popBack (List*);
void popCurrent (List*);
void cleanList (List*);
void* first (List*);
void* next (List*);
void* last (List*);
void* prev (List*);

#endif
