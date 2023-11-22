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

}

void
test_charset_contains_text (void)
{

}

void
test_charset_remove_text (void)
{

}

// Who am I?
// Resides in me.
// Something you would not want to hear
// Something I wouldn't tell you

void
test_charset_clone (void)
{

}

int main() {
  test_charset_add_text ();
  test_charset_contains_text ();
  test_charset_remove_text ();
  test_charset_clone ();

  return 0;
}
