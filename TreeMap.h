#ifndef TREEMAP_H
#define TREEMAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
   void* data;
   int key;
   struct node* left;
   struct node* right;
   struct node* parent;
}tree_node;

typedef struct{
   tree_node* root;
   tree_node* current;
}TreeMap;

TreeMap* createTreeMap();
tree_node* _crearNodo(int key, void* dato);
void insert(TreeMap* tree, int key, void* dato);
void* search(TreeMap* tree, int key);
void erase(TreeMap* tree, int key);
void* first(TreeMap* tree);
void* next(TreeMap* tree);


#endif // TREEMAP_H
