#include <stdlib.h>
#include "List.h"


void cleanList (List* list)
{
    list -> first = NULL;
    list -> current = NULL;
    list -> last = NULL;
}
List* createList ()
{
   List* list = (List*) malloc (sizeof (List));
   list -> first = NULL;
   list -> current = NULL;
   list -> last = NULL;
   return list;
}
node* createNode (void* data)
{
    node* n;
    n = (node*) malloc (sizeof (node));
    n -> data = data;
    n -> next = NULL;
    n -> prev = NULL;
    return n;
}
int is_empty(List* list) {return (list->first==NULL);}
void popFront (List* list){
    if (!is_empty(list))
    {
        node *n = list -> first;
        list -> first = list -> first -> next;
        if (list -> first != NULL) list-> first -> prev = NULL;
        else list -> last = NULL;
        free(n);
    }
}
void popBack (List* list){
    if(!is_empty(list)){
        node *n = list->last;
        list->last=list->last->prev;
        if(list->last!=NULL) list->last->next=NULL;
        else list->first=NULL;
        free(n);
    }
}
void pushFront (List* list, void* data)
{
    node *n;
    n = createNode (data);
    if (is_empty(list)) list -> last = n;
    else list -> first -> prev = n;
    n -> next = list -> first;
    list -> first = n;
}
void pushBack(List* list, void* data)
{
    node *n;
    n = createNode(data);
    if (is_empty(list)) list -> first = n;
    else list -> last -> next = n;
    n -> prev = list -> last;
    list -> last = n;
}
void pushCurrent (List* list, void* data)
{
    if (!list->current) return;
    node* a = createNode(data);
    a -> next = list -> current -> next;
    list -> current -> next = a;
    if (a->next) a -> next -> prev = a;
    a -> prev = list -> current;
    if (list -> current == list -> last) list -> last = a;
    list -> current = a;
}
void popCurrent (List* list)
{
    if(!list -> current) return;
    if (list -> current -> prev) list -> current -> prev -> next = list -> current -> next;
    if (list -> current -> next) list -> current -> next -> prev = list -> current -> prev;
    if (list -> first == list -> current) list -> first = list -> current -> next;
    if (list -> last == list -> current) list -> last = list -> current -> prev;
    free (list -> current);
}
void* first (List* list)
{
    if(is_empty(list)) return NULL;
    list -> current = list -> first;
    return (list -> first -> data);
}
void* next(List* list)
{
    if(list->current) list->current=list->current->next;
    if(list->current) return list->current->data;
    else return NULL;
}
void* last(List* list)
{
    if(list->last)
    {
        list->current=list->last;
        return list->last->data;
    }
    else return NULL;
}
void* prev(List* list)
{
    if(list->current) list->current=list->current->prev;
    if(list->current) return list->current->data;
    else return NULL;
}
