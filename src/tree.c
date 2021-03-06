/*
 * Implementation of the tree methods.
 */

#include "tree.h"

#include <stddef.h>
#include <stdlib.h>

// declaration of a function that is defined below
Tree_node* create_node_child(Tree_node* parent, char symbol, int type);


/*
 * Searches for a node with the given symbol among the child of the given node.
 */
Tree_node* get_create_node_child(Tree_node* parent, char symbol, int type) {
  // walk through every child node, until we find a corresponding symbol, or stop at last node
  Tree_node* current_node = parent->child;
  while(current_node != NULL) {
    if (current_node->symbol == symbol) { // found correct node
      return current_node;
    }
    current_node = current_node->sibling;
  }

  // the correct node was not found, create a new one and put it as the first one
  Tree_node* new_node = create_node_child(parent, symbol, type);
  new_node->sibling = parent->child;
  parent->child = new_node;

  return new_node;
}

/*
 * Creates a node and associates the given node as its parent and the given symbol as its own.
 */
Tree_node* create_node_child(Tree_node* parent, char symbol, int type) {
  Tree_node* child = new_Tree_node();
  child->symbol = symbol;
  child->parent = parent;

  // allocate memory for the data structure corresponding to the given type.
  if (type == BIC) {
    child->bic_data = (Bic_data*) malloc(sizeof(Bic_data));
  } else if (type == PROB){
    child->prob_data = (Prob_data*) malloc(sizeof(Prob_data));
  }

  return child;
}

/*
 * Frees the memory used by a node, its childs and siblings.
 */
void free_node(Tree_node* node) {
  if (node->bic_data != NULL) {
    free(node->bic_data);
  }
  if (node->prob_data != NULL) {
    free(node->prob_data);
  }
  if (node->child != NULL) {
    free_node(node->child);
  }
  if (node->sibling != NULL) {
    free_node(node->sibling);
  }
  free(node);
}

/*
 * Searches for a node with the given symbol among the child of the given node.
 */
Tree_node* get_child_node(Tree_node* parent, char symbol) {
  if (parent == NULL) {
    return NULL;
  }
  // walk through every child node, until we find a corresponding symbol, or stop at last node
  Tree_node* current_node = parent->child;
  while(current_node != NULL && current_node->symbol != symbol) {
    current_node = current_node->sibling;
  }
  return current_node;
}

/*
 * Instantiates a new Tree_node and set its default values
 */
Tree_node* new_Tree_node() {
  Tree_node* node = (Tree_node*) malloc(sizeof(Tree_node));
  node->child = NULL;
  node->sibling = NULL;
  node->parent = NULL;
  node->prob_data = NULL;
  node->bic_data = NULL;
  return node;
}
