#include <stdio.h>
#include "tree.h"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define COLOR_RESET "\e[0m"

int main() {
  Tree *tree = tree_new ();

  tree_insert (tree, 'c', 2);
  tree_insert (tree, 'd', 3);
  tree_insert (tree, 'a', 1);
  tree_insert (tree, 'b', 4);

  if (tree_get_size (tree) == 10) {
    printf ("%sTest: tree_get_size -> Passed%s\n", GRN, COLOR_RESET);
  } else {
    printf ("%sTest: tree_get_size -> Failed%s\n", RED, COLOR_RESET);
  }

  if (tree_get_char_count (tree, 'a') == 1) {
    printf ("%sTest: tree_get_char_count 1 -> Passed%s\n", GRN, COLOR_RESET);
  } else {
    printf ("%sTest: tree_get_char_count 1 -> Failed%s\n", RED, COLOR_RESET);
  }

  if (tree_get_char_count (tree, 'b') == 4) {
    printf ("%sTest: tree_get_char_count 2 -> Passed%s\n", GRN, COLOR_RESET);
  } else {
    printf ("%sTest: tree_get_char_count 2 -> Failed%s\n", RED, COLOR_RESET);
  }

  tree_delete (tree, 'a');

  if (tree_get_char_count (tree, 'a') == 0) {
    printf ("%sTest: tree_delete -> Passed%s\n", GRN, COLOR_RESET);
  } else {
    printf ("%sTest: tree_delete -> Failed%s\n", RED, COLOR_RESET);
  }

  tree_replace (tree, 'b', 6);

  if (tree_get_char_count (tree, 'b') == 6) {
    printf ("%sTest: tree_replace 2 -> Passed%s\n", GRN, COLOR_RESET);
  } else {
    printf ("%sTest: tree_replace -> Failed%s\n", RED, COLOR_RESET);
  }

  //FIXME: Add TreeIterator test

  tree_unref (tree);

  return 0;
}
