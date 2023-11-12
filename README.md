# Charset

Charset is a fun data structure that is used to store characters and there frequencies. It was implemented in [Crosswords](https://gitlab.gnome.org/jrb/libipuz/-/blob/master/libipuz/ipuz-charset.c?ref_type=heads) by Jonathan Blandford and Federico Mena.

This implementation from scratch is done for learning purposes.

## Todo
- [ ] Migrate to cmake
- [ ] Create a seperate test suite, implement all tests similar to [IPuzCharset](https://gitlab.gnome.org/jrb/libipuz/-/blob/master/libipuz/tests/charset.c?ref_type=heads) and make sure they all are passing
- [ ] Implement TreeIterator (priority)
- [ ] Buffer the input text in a string and flush it when needed
```c
// We will buffer the characters when we call _set_text
// We need to separetely implement this, we internally append it a buf_string
void charset_buffer_text (Charset *charset);

/*
 * return the buffered string
 *
 * but what if we remove some text before calling _flush, can we maintain an order? (Need to think)
 */
const char *charset_flush_text (Charset *charset);
```
- [ ] ...
