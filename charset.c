#include "charset.h"

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
charset_contains_text (Charset    *charset,
                       const char *text)
{

}

bool
charset_remove_text (Charset    *charset,
                     const char *text)
{

}
