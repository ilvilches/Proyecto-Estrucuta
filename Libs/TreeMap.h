#ifndef TREEMAP_H
#define TREEMAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
void  tree_insert(TreeMap* tree, int key, void* dato);
void* tree_search(TreeMap* tree, int key);
void  tree_erase(TreeMap* tree, int key);
void* tree_first(TreeMap* tree);
void* tree_next(TreeMap* tree);


#endif // TREEMAP_H
