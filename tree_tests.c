#include <stdio.h>
#include <assert.h>
#include "tree.h"

/*
 * Our tree for tesing looks like
 *
 *                  {c, 2}
 *                /       \
 *             {a, 1}    {d, 3}
 *                 \
 *                {b, 4}
 *
 */

#define BLACK      "\033[0;30m"
#define GREEN      "\033[0;32m"
#define RESET      "\033[0;m"

void
log_message (int num, char *message)
{
  if (num == 1)
    printf ("%sLOGS:%s START of %s%s%s\n", GREEN, RESET, BLACK, message, RESET);
  else if (num == 2)
    printf ("%sLOGS:%s END of %s%s%s\n", GREEN, RESET, BLACK, message, RESET);
}

void
test_tree_insert (void)
{
  log_message (1, "test_tree_insert");
  Tree *tree = tree_new ();

  tree_insert (tree, 'c', 2);
  tree_insert (tree, 'd', 3);
  tree_insert (tree, 'a', 1);
  tree_insert (tree, 'b', 4);

  assert (tree_get_size (tree) == 10);
  assert (tree_get_char_count (tree, 'a') == 1);
  assert (tree_get_char_count (tree, 'b') == 4);
  assert (tree_get_char_count (tree, 'c') == 2);
  assert (tree_get_char_count (tree, 'd') == 3);

  tree_unref (tree);

  log_message (2, "test_tree_insert");
}

void
test_tree_delete (void)
{
  log_message (1, "test_tree_delete");
  Tree *tree = tree_new ();

  tree_insert (tree, 'c', 2);
  tree_insert (tree, 'd', 3);
  tree_insert (tree, 'a', 1);
  tree_insert (tree, 'b', 4);

  assert (tree_get_char_count (tree, 'a') == 1);

  tree_delete (tree, 'a');

  assert (tree_get_char_count (tree, 'a') == 0);

  /* Making sure we are still retaining the root */
  tree_delete (tree, 'c');

  assert (tree_get_char_count (tree, 'd') == 3);

  tree_unref (tree);

  log_message (2, "test_tree_insert");
}

void
test_tree_replace (void)
{
  log_message (1, "test_tree_replace");
  Tree *tree = tree_new ();

  tree_insert (tree, 'c', 2);
  tree_insert (tree, 'd', 3);
  tree_insert (tree, 'a', 1);
  tree_insert (tree, 'b', 4);

  assert (tree_get_char_count (tree, 'a') == 1);
  tree_replace (tree, 'a', 5);
  assert (tree_get_char_count (tree, 'a') == 5);

  assert (tree_get_char_count (tree, 'b') == 4);
  tree_replace (tree, 'b', 1);
  assert (tree_get_char_count (tree, 'b') == 1);

  tree_unref (tree);

  log_message (2, "test_tree_replace");
}

// Those to whom evil is done,
// shall do evil in return

void
test_tree_clone_equal (void)
{
  log_message (1, "test_tree_clone_equal");
  Tree *tree_a, *tree_b;

  tree_a = tree_new ();

  tree_insert (tree_a, 'c', 2);
  tree_insert (tree_a, 'd', 3);
  tree_insert (tree_a, 'a', 1);
  tree_insert (tree_a, 'b', 4);

  tree_b = tree_clone (tree_a);

  assert (tree_equal (tree_a, tree_b) == true);

  tree_replace (tree_b, 'a', 4);

  assert (tree_equal (tree_a, tree_b) == false);

  tree_unref (tree_a);
  tree_unref (tree_b);

  log_message (2, "test_tree_clone_equal");
}

void
assert_value (TreeNodeValue value, char c, uint count)
{
  assert (value.c == c);
  assert (value.count == count);
}

void
test_tree_iterator (void)
{
  log_message (1, "test_tree_iterator");
  Tree *tree = tree_new ();
  TreeIterator *iter;
  TreeNodeValue value;

  tree_insert (tree, 'c', 2);
  tree_insert (tree, 'd', 3);
  tree_insert (tree, 'a', 1);
  tree_insert (tree, 'b', 4);

  iter = tree_iter_init (tree);

  assert (tree_iter_has_next (iter) == true);
  value =  tree_node_next (iter);
  assert_value (value, 'a', 1);

  assert (tree_iter_has_next (iter) == true);
  value =  tree_node_next (iter);
  assert_value (value, 'b', 4);

  assert (tree_iter_has_next (iter) == true);
  value =  tree_node_next (iter);
  assert_value (value, 'c', 2);

  assert (tree_iter_has_next (iter) == true);
  value =  tree_node_next (iter);
  assert_value (value, 'd', 3);

  assert (tree_iter_has_next (iter) == false);

  tree_iter_free (iter);
  tree_unref (tree);

  log_message (2, "test_tree_iterator");
}

// Ignorant, Unimaginative people
// consumed by self-interest

int main() {
  test_tree_insert ();
  test_tree_delete ();
  test_tree_replace ();
  test_tree_clone_equal ();
  test_tree_iterator ();

  return 0;
}
