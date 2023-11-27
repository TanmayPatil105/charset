#include <stdio.h>
#include <assert.h>
#include "charset.h"

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
test_charset_add_text (void)
{
  log_message (1, "test_charset_add_text");

  Charset *charset = charset_new ();

  charset_add_text (charset, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCD");

  assert (charset_get_n_chars (charset) == 26);
  assert (charset_get_size (charset) == 30);
  assert (charset_get_char_count (charset, 'A') == 2);
  assert (charset_get_char_count (charset, 'D') == 2);
  assert (charset_get_char_count (charset, 'Z') == 1);

  charset_free (charset);

  log_message (2, "test_charset_add_text");
}

void
test_charset_contains_text (void)
{
  log_message (1, "test_charset_contains_text");

  Charset *charset = charset_new ();

  charset_add_text (charset, "AABBCCDDEEFFG");

  assert (charset_contains_text (charset, "ABCDEFG"));
  assert (!charset_contains_text (charset, "TEXT"));

  charset_free (charset);

  log_message (2, "test_charset_contains_text");
}

void
test_charset_remove_text (void)
{
  log_message (1, "test_charset_remove_text");

  Charset *charset = charset_new ();

  charset_add_text (charset, "AABBCCDDEEFFG");

  assert (!charset_remove_text (charset, "TEXT"));
  assert (charset_remove_text (charset, "ABCDEF"));
  assert (charset_get_size (charset) == 7);

  charset_free (charset);

  log_message (2, "test_charset_remove_text");
}

// Who am I?
// Resides in me.
// Something you would not want to hear
// Something I wouldn't tell you

void
test_charset_clone (void)
{
  log_message (1, "test_charset_clone");

  Charset *charset_a, *charset_b;

  charset_a = charset_new ();
  charset_add_text (charset_a, "AABBCCDDEEFFGG");

  charset_b = charset_clone (charset_a);

  assert (charset_equal (charset_a, charset_b));

  charset_free (charset_a);
  charset_free (charset_b);

  log_message (2, "test_charset_clone");
}

int main() {
  test_charset_add_text ();
  test_charset_clone ();
  test_charset_contains_text ();
  test_charset_remove_text ();

  return 0;
}
