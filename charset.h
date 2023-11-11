#pragma once

#include "tree.h"

typedef struct Charset {
  Tree *tree;
  int ref_count;
} Charset;
