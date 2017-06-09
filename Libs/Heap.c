#include "Heap.h"
#include "stdlib.h"
#include "stdio.h"


Heap* createHeap(){
   Heap *pq=(Heap*) malloc(sizeof(Heap));
   pq->heapArray=(heapElem*) malloc(4*sizeof(heapElem));
   pq->size=0;
   pq->capac=3; //capacidad inicial
   return pq;
}

void* heap_top(Heap* pq){
    if(pq->size==0)
        return NULL;
    return pq->heapArray[1].data;
}

int size(Heap* pq){
   return pq->size;
}

void heap_push(Heap* pq, void* data, int priority){
    pq->size++;

    if(pq->size>pq->capac){
        pq->capac=(pq->capac+1)*2-1;
        pq->heapArray=realloc(pq->heapArray, (pq->capac+1)*sizeof(heapElem));
    }

    /*Flotación*/
    int now = pq->size;
    while(pq->heapArray[now/2].priority < priority)
        {
                pq->heapArray[now] = pq->heapArray[now/2];
                now /= 2;
        }
    pq->heapArray[now].priority = priority;
    pq->heapArray[now].data = data;
}

void heap_pop(Heap* pq){

        pq->heapArray[1] = pq->heapArray[pq->size--];
        int priority=pq->heapArray[1].priority;

        /*Hundimiento*/
        int now = 2;
        while((now<=pq->size && pq->heapArray[now].priority > priority) || (now+1<=pq->size && pq->heapArray[now+1].priority > priority)){
          heapElem tmp=pq->heapArray[now/2];
          if(now+1<=pq->size && pq->heapArray[now].priority<pq->heapArray[now+1].priority) now++;

          pq->heapArray[now/2]=pq->heapArray[now];
          pq->heapArray[now]=tmp;

          now *= 2;
        }
}
