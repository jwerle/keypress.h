keypress.h
==========

Listen for key press from stdin

## install

```sh
$ clib install jwerle/keypress.h
```

## usage

To listen for keys pressed in stdin create a function with the following
signature that returns 0 for success and -1 on failure which ends the
listen loop.

```c
static void
on_keypress (int ch, key_t *key);
```

## example

```c

#include "keypress.h"

static int
on_keypress (int ch, key_t *key);

int
main (void) {
  keypress_listen(on_keypress);
  return 0;
}

static int
on_keypress (int ch, key_t *key) {
  if (ch == KEY_QUIT) {
    return -1;
  }

  printf("%s = %d\n", key->name, ch);

  return 0;
}
```

## todo

- handle escape key
- async?

## license

MIT
