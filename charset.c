#include <stdio.h>
#include "charset.h"
#include "tree-node.h"

Charset*
charset_new ()
{
  Charset *charset = (Charset *) malloc(sizeof (Charset));

  charset->tree = tree_new ();
  charset->ref_count = 0;

  return charset;
}

void
charset_add_text (Charset    *charset,
                  const char *text)
{
  char c;
  const char *str = text;

  for (c = *str; c != '\0'; c = *++str)
    {
      TreeNode *node;

      node = tree_lookup_node (charset->tree, c);

      if (node == NULL)
        {
          tree_insert (charset->tree, c, 1);
        }
      else
        {
          uint count = tree_node_get_count (node);
          tree_replace (charset->tree, c, count + 1);
        }
    }
}

uint
charset_get_char_count (Charset *charset,
                        char     c)
{
  return tree_get_char_count (charset->tree, c);
}

size_t
charset_get_n_chars (Charset *charset)
{
  return tree_get_n_nodes (charset->tree);
}

size_t
charset_get_size (Charset *charset)
{
  return tree_get_size (charset->tree);
}

bool
charset_equal (Charset *charset_a,
               Charset *charset_b)
{
  return tree_equal (charset_a->tree,
                     charset_b->tree);
}

Charset*
charset_clone (Charset *charset)
{
  Charset *cloned = (Charset *) malloc(sizeof (Charset));

  cloned->tree = tree_clone (charset->tree);
  cloned->ref_count = 0;

  return cloned;
}

bool
charset_contains_text (Charset    *charset,
                       const char *text)
{
  char c;
  const char *str = text;
  Charset *cloned_charset = charset_clone (charset);

  for (c = *str; c != '\0'; c = *++str)
    {
      TreeNode *node;
      node = tree_lookup_node (cloned_charset->tree, c);

      if (node != NULL)
        {
          uint count = tree_node_get_count (node);

          if (count == 1)
            tree_delete (cloned_charset->tree, c);
          else
            tree_replace (cloned_charset->tree, c, count - 1);
        }
      else
        {
          return false;
        }
    }

  return true;
}

bool
charset_remove_text (Charset    *charset,
                     const char *text)
{
  char c;
  const char *str = text;

  if (!charset_contains_text (charset, text))
    return false;

  for (c = *str; c != '\0'; c = *++str)
    {
      TreeNode *node;

      node = tree_lookup_node (charset->tree, c);

      if (node != NULL)
        {
          uint count = tree_node_get_count (node);

          if (count == 1)
            tree_delete (charset->tree, c);
          else
            tree_replace (charset->tree, c, count - 1);
        }
    }

  return true;
}
