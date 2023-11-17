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

void
test_tree_insert (void)
{
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
}

void
test_tree_delete (void)
{
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
}

void
test_tree_replace (void)
{
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
}

// Those to whom evil is done,
// shall do evil in return

void
test_tree_clone_equal (void)
{
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
}

void
test_tree_iterator (void)
{

}

int main() {
  test_tree_insert ();
  test_tree_delete ();
  test_tree_replace ();
  test_tree_clone_equal ();

  return 0;
}
