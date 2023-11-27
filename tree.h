#pragma once

#include <stdlib.h>
#include "tree-node.h"

typedef struct Tree {
  TreeNode *root;
  int ref_count;
} Tree;

Tree*         tree_new            (void);
void          tree_insert         (Tree         *tree,
                                   char          key,
                                   uint          count);
void          tree_replace        (Tree         *tree,
                                   char          key,
                                   uint          count);
TreeNode     *tree_lookup_node    (Tree         *tree,
                                   char          key);
void          tree_delete         (Tree         *tree,
                                   char          key);
size_t        tree_get_size       (Tree         *tree);
size_t        tree_get_n_nodes    (Tree         *tree);
uint          tree_get_char_count (Tree         *tree,
                                   char          key);
Tree         *tree_clone          (Tree         *tree);
bool          tree_equal          (Tree         *tree_a,
                                   Tree         *tree_b);
void          tree_unref          (Tree         *tree);
TreeIterator *tree_iter_init      (Tree         *tree);
bool          tree_iter_has_next  (TreeIterator *iter);
TreeNodeValue tree_node_next      (TreeIterator *iter);
void          tree_iter_free      (TreeIterator *iter);
