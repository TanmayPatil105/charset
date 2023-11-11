#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
  char key;
  uint count;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

TreeNode *tree_node_new            (char      key,
                                    uint      count);
TreeNode *tree_node_insert         (TreeNode *node,
                                    char      key,
                                    uint      count);
TreeNode *tree_node_get_node       (TreeNode *node,
                                    char      key);
TreeNode *tree_node_delete_node    (TreeNode *node,
                                    char      key);
size_t    tree_node_get_size       (TreeNode *node);
size_t    tree_node_count_nodes    (TreeNode *node);
void      tree_node_replace        (TreeNode *node,
                                    uint      count);
