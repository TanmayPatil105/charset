#include "tree-node.h"

TreeNode*
tree_node_new (char key,
               uint count)
{
  TreeNode *node = (TreeNode *) malloc(sizeof (TreeNode));

  node->key = key;
  node->count = count;
  node->left = NULL;
  node->right = NULL;

  return node;
}

TreeNode*
tree_node_insert (TreeNode *node,
                  char      key,
                  uint      count)
{
  if (node == NULL)
    return tree_node_new (key, count);

  if (key < node->key)
    node->left = tree_node_insert (node->left, key, count);
  else if (key > node->key)
    node->right = tree_node_insert (node->right, key, count);

  return node;
}

/*
 * Search function
 */
TreeNode*
tree_node_get_node (TreeNode *node,
                    char      key)
{
  if (node == NULL ||
      node->key == key)
    return node;

  if (node->key > key)
    return tree_node_get_node (node->left, key);

  return tree_node_get_node (node->right, key);
}

static void
tree_node_copy (TreeNode *src_node,
                TreeNode *dst_node)
{
  if (!src_node || !dst_node)
    return;

  dst_node->key = src_node->key;
  dst_node->count = src_node->count;
}

TreeNode*
tree_node_delete_node (TreeNode *node,
                       char      key)
{
  if (node == NULL)
    return node;

  if (node->key > key)
    {
      node->left = tree_node_delete_node (node->left, key);
      return node;
    }
  else if (node->key < key)
    {
      node->left = tree_node_delete_node (node->right, key);
      return node;
    }

  /*
   * We are at node->key == key
   */
  if (node->left == NULL)
    {
      TreeNode *new_root = node->right;
      free (node);
      return new_root;
    }
  else if (node->right == NULL)
    {
      TreeNode *new_root = node->left;
      free (node);
      return new_root;
    }
  else
    {
      /*
       * 1. Find the successor
       * 2. Remove the successor
       * 3. Copy data of successor to root
       * 4. Delete the successor
       */
      TreeNode *parent = node;

      TreeNode *succ = node->right;
      while (succ->left != NULL)
        {
          parent = succ;
          succ = succ->left;
        }

      if (parent != node)
        parent->left = succ->right;
      else
        parent->right = succ->right;

      tree_node_copy (succ, node);

      free (succ);

      return node;
   }
}

static uint
tree_node_get_size_helper (TreeNode *node)
{
  if (node == NULL)
    return 0;

  return node->count
         + tree_node_get_size_helper (node->left)
         + tree_node_get_size_helper (node->right);
}

size_t
tree_node_get_size (TreeNode *node)
{
  return (size_t)tree_node_get_size_helper (node);
}

void
tree_node_replace (TreeNode *node,
                   uint      new_count)
{
  node->count = new_count;
}
