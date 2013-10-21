
#include "keypress.h"

static int
on_keypress (int ch, keypress_t *key);

int
main (void) {
  keypress_listen(on_keypress);
  return 0;
}

static int
on_keypress (int ch, keypress_t *key) {
  if (ch == KEY_QUIT) {
    return -1;
  }

  printf("%s = %d\n", key->name, ch);

  return 0;
}
