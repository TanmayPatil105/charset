#include "tree.h"

Tree*
tree_new ()
{
  Tree* tree = (struct Tree*) malloc(sizeof (struct Tree));

  tree->root = NULL;
  tree->ref_count = 0;

  return tree;
}

void
tree_insert (Tree *tree,
             char  key,
             uint  count)
{
  tree->root = tree_node_insert (tree->root, key, count);
}

void
tree_replace (Tree *tree,
              char  key,
              uint  new_count)
{
  TreeNode *node = tree_node_get_node (tree->root, key);

  if (node != NULL)
    {
      tree_node_replace (node, new_count);
    }
}

TreeNode*
tree_lookup_node (Tree *tree,
                  char  key)
{
  TreeNode *node;

  node = tree_node_get_node (tree->root, key);

  if (node == NULL)
    return NULL;

  return node;
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

size_t
tree_get_n_nodes (Tree *tree)
{
  return tree_node_count_nodes (tree->root);
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

Tree*
tree_clone (Tree *tree)
{
  Tree *clone = tree_new ();

  clone->root = tree_node_clone (tree->root);

  return clone;
}

bool
tree_equal (Tree *tree_a,
            Tree *tree_b)
{
  return tree_node_equal (tree_a->root,
                          tree_b->root);
}

void
tree_unref (Tree *tree)
{
  // Iterator and clean up nodes
  tree_node_free (tree->root);
}

TreeIterator*
tree_iter_init (Tree *tree)
{
  TreeIterator *iter = (TreeIterator *) malloc (sizeof (TreeIterator));

  iter->size = tree_node_count_nodes (tree->root);
  iter->inorder = tree_node_get_inorder (tree->root);
  iter->index = 0;

  return iter;
}

// it's race against the watch
// but we don't wanna watch

bool
tree_iter_has_next (TreeIterator *iter)
{
  if (iter &&
      (size_t)iter->index < iter->size)
    return true;

  return false;
}

/*
 * Must be called after calling `tree_iter_has_next`
 */
TreeNodeValue
tree_node_next (TreeIterator *iter)
{
  if (iter == NULL)
    return (TreeNodeValue) {
      .c = 0,
      .count = -1,
    };

  return iter->inorder[iter->index];
}
