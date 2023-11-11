#pragma once

#include <stdlib.h>
#include "tree-node.h"

typedef struct Tree {
  TreeNode *root;
  int ref_count;
} Tree;

Tree*     tree_new            (void);
void      tree_insert         (Tree* tree,
                               char  key,
                               int   count);
void      tree_replace        (Tree* tree,
                               char  key,
                               int   count);
void      tree_delete         (Tree* tree,
                               char  key);
size_t    tree_get_size       (Tree *tree);
size_t    tree_get_n_nodes    (Tree *tree);
uint      tree_get_char_count (Tree *tree,
                               char  key);
TreeNode* tree_find_key       (Tree* tree,
                               char  key);
