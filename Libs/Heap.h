#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct heapElem
{
   void* data;
   int priority;
}
heapElem;

typedef struct
{
  heapElem* heapArray;
  int size;
  int capac;
}
Heap; //Monticulo



Heap* createHeap ();
void* heap_top(Heap* pq);
int size(Heap* pq);
void heap_push(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);

#endif // HEAP_H_INCLUDED
