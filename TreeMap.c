#include <stdio.h>
#include <stdlib.h>
#include "TreeMap.h"

TreeMap* createTreeMap(){
    TreeMap* arbol = (TreeMap*)malloc(sizeof(TreeMap));
    arbol -> root = NULL;
    arbol -> current = NULL;
    return(arbol);
}

tree_node* _crearNodo(int key, void* dato){
    tree_node* a = (tree_node*)malloc(sizeof(tree_node));
    a -> data = dato;
    a -> key = key;
    a -> left = NULL;
    a -> right = NULL;
    a -> parent = NULL;
    return(a);
}

void insert(TreeMap* tree, int key, void* dato){
    int validador = 0;
    tree_node* Newnodo = _crearNodo(key,dato);
    if(tree->root == NULL){
       tree->root = Newnodo;
        tree->current = Newnodo;
    }
    else{
        tree->current = tree->root;
            while(validador == 0){
                if(tree->current->key == key){
                    validador=1;
                    break;
                }
                if(tree->current->key < key){
                    if(tree->current->right == NULL){
                        tree->current->right = Newnodo;
                        tree->current->right->parent = tree->current;
                        validador=1;
                        break;
                    }
                    tree->current = tree->current->right;
                }
                else{
                    if(tree->current->left == NULL){
                        tree->current->left = Newnodo;
                        tree->current->left->parent = tree->current;
                        validador=1;
                        break;
                    }
                    tree->current = tree->current->left;
                }
            }
    }
}

void* search(TreeMap* tree, int key){
    tree->current = tree->root;
    while(tree -> current){
        if(tree -> current -> key == key){
            return(tree -> current -> data);
        }
        else{
            if(tree -> current -> key < key){
                tree -> current = tree -> current -> right;
            }
            else{
                tree ->current = tree -> current -> left;
            }
        }
    }
    return NULL;
}

void erase(TreeMap* tree, int key){
    tree -> current = tree -> root;
    tree_node* a = (tree_node*)malloc(sizeof(tree_node));
    void* aux = search(tree,key);
    if(aux){
      aux = NULL;
      free(aux);
    }
    else{
        tree-> current = NULL;
        free(tree -> current);
    }
    if((tree -> current -> right == NULL) && (tree -> current -> left == NULL)){
        /* por si no tiene hijos*/
        tree -> current ->data = NULL;
        tree -> current -> key = 0;
    }
    else{
        if((tree -> current -> left != NULL) && (tree -> current -> right != NULL)){
            /* en caso de que tenga 2 hijos*/
            a = tree -> current -> left;
            while(a -> right){
                a = a -> right;
            }
            if(a -> left){
                a -> left -> parent = a -> parent;
            }
            else{
                a ->parent -> right = NULL;
            }
            tree -> current -> key = a -> key;
            tree -> current -> data = a -> data;
            a -> data = NULL;
            free(a);
        }
        else{
            if(tree -> current -> left){
                tree -> current -> left -> parent = tree -> current -> parent;
                tree -> current ->data = NULL;
            }

            if(tree -> current -> right){
                tree -> current -> right -> parent = tree -> current -> parent;
                tree -> current ->data = NULL;
            }
        }
    }
}

void* first(TreeMap* tree){
    tree ->current = tree -> root;
    return tree -> root -> data;
}
