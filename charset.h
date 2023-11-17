#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct Charset {
  Tree *tree;
  int ref_count;
} Charset;

Charset *charset_new            (void);
void     charset_add_text       (Charset    *charset,
                                 const char *text);
uint     charset_get_char_count (Charset    *charset,
                                 char        c);
size_t   charset_get_n_chars    (Charset    *charset);
size_t   charset_get_size       (Charset    *charset);
Charset *charset_clone          (Charset    *charset);
bool     charset_contains_text  (Charset    *charset,
                                 const char *text);
bool     charset_remove_text    (Charset    *charset,
                                 const char *text);
