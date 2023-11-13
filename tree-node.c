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

uint
tree_node_get_count (TreeNode *node)
{
  if (node == NULL)
    return 0;

  return node->count;
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
tree_node_get_count_helper (TreeNode *node,
                            bool      get_size)
{
  uint count = 1;
  if (node == NULL)
    return 0;

  if (get_size)
    count = node->count;

  return count
         + tree_node_get_count_helper (node->left, get_size)
         + tree_node_get_count_helper (node->right, get_size);
}

size_t
tree_node_get_size (TreeNode *node)
{
  return (size_t)tree_node_get_count_helper(node, true);
}

size_t
tree_node_count_nodes (TreeNode *node)
{
  return (size_t)tree_node_get_count_helper(node, false);
}

void
tree_node_replace (TreeNode *node,
                   uint      new_count)
{
  node->count = new_count;
}

static void
inorder (TreeNode      *node,
         TreeNodeValue *tree_inorder,
         int           *index)
{
  TreeNodeValue value;
  if (node == NULL)
    return;

  inorder (node->left, tree_inorder, index);

  value = (TreeNodeValue) {
    .c = node->key,
    .count = node->count,
  };
  tree_inorder[*index++] = value;

  inorder (node->right, tree_inorder, index);
}

TreeNodeValue*
tree_node_get_inorder (TreeNode *node)
{
  int index = 0;
  TreeNodeValue *tree_inorder;
  size_t n_nodes = tree_node_count_nodes (node);

  if (n_nodes == 0)
    return NULL;

  tree_inorder = (TreeNodeValue *) malloc (sizeof (TreeNodeValue) * n_nodes);

  inorder (node, tree_inorder, &index);

  return tree_inorder;
}
