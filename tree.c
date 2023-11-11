#include "tree.h"

Tree*
tree_new ()
{
  Tree* tree = (struct Tree*) malloc(sizeof (struct Tree));

  tree->ref_count = 0;

  return tree;
}

void
tree_insert (Tree *tree,
             char  key,
             int   count)
{
  tree->root = tree_node_insert (tree->root, key, count);
}

void
tree_replace (Tree *tree,
              char  key,
              int   new_count)
{
  TreeNode *node = tree_node_get_node (tree->root, key);

  if (node != NULL)
    {
      tree_node_replace (node, new_count);
    }
}

void
tree_delete (Tree *tree,
             char  key)
{
  tree->root = tree_node_delete_node (tree->root, key);
}

size_t
tree_get_size (Tree *tree)
{
  return tree_node_get_size (tree->root);
}

uint
tree_get_char_count (Tree *tree,
                     char  key)
{
  TreeNode *node = tree_node_get_node (tree->root, key);

  if (node == NULL)
    return 0;

  return node->count;
}

TreeNode*
tree_lookup (Tree *tree,
             char  key)
{
  return tree_node_get_node (tree->root, key);
}
