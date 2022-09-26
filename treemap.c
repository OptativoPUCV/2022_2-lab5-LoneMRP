#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
        TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
        new->lower_than = lower_than;
        return new;

}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
   /*tree->current=tree->root;
    if(tree->current==NULL){
      TreeNode * new = createTreeNode(key,value);
      tree->root=new;
    }
    while(tree->current!=NULL ){
      if(is_equal(tree,tree->current->pair->key,key)){

        return;
      }else{
        if(tree->lower_than(tree->current->pair->key,key)){
          tree->current = tree->current->right;

        }else{
          tree->current = tree->current->left;

        }
      }
  }

  TreeNode * new = createTreeNode(key,value);
  if(tree->current==NULL)
      tree->root=new;
    else{
      new->parent=tree->current;
      if(tree->current->pair->key>key)
        tree->current->left=new;
      else  
        tree->current->right=new;
  }
*/

}

TreeNode * minimum(TreeNode * x){
  if(x->left == NULL)
    return x;
  else{
    while (x->left != NULL){
      x = x->left;
    }
    return x;
  }
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    tree->current=tree->root;
    while(tree->current!=NULL ){
      if(is_equal(tree,tree->current->pair->key,key)){
        return tree->current->pair;
      }else{
        if(tree->lower_than(tree->current->pair->key,key)){
          tree->current = tree->current->right;
        }else{
          tree->current = tree->current->left;
        }
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode* aux = (TreeNode *)malloc(sizeof(TreeNode));
  tree->current=tree->root;
  while(tree->current!=NULL ){
    if(is_equal(tree,tree->current->pair->key,key)){
      return tree->current->pair;
    }
    else{
      if(tree->lower_than(tree->current->pair->key,key)){
        aux->pair = tree->current->pair;
        tree->current = tree->current->right;
      }
      else{
        aux->pair = tree->current->pair;
        tree->current = tree->current->left;
      }
    }
  }
  printf("%s",tree->current->pair->key);
  printf("%s",aux->pair->key);
  return aux->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
  tree->current = tree->root;
  while(tree->current->left != NULL){
    tree->current = tree->current->left;
  }
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree->current->right != NULL){
    tree->current = tree->current->right;
    if(tree->current->left != NULL){
      while(tree->current->left != NULL){
        tree->current = tree->current->left;
      }
    }
  }
  else{
    if(tree->current->pair->key < tree->current->parent->pair->key)
      tree->current=tree->current->parent;
    else
      tree->current=tree->current->parent->parent;
  }
  return tree->current->pair;
  }