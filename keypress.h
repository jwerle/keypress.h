#ifndef KEYPRESS_H
#define KEYPRESS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usleep.h"
#include "getch.h"

#define KEY_QUIT 4


// PROTOTYPE

typedef struct key {
  char *name;
//  int ctrl;
//  int meta;
//  int shift;
//  int arrow;
} keypress_t;

typedef int (*keypress_cb)(int ch, keypress_t *key);

void
keypress_listen (keypress_cb cb);


static void
key_reset (keypress_t *key);


// IMPLEMENTATION

void
keypress_listen (keypress_cb cb) {
  int ch = -1;
  int in_sequence = 0;
  int sequence[3];
  int i = 0;
  int rc = 0;
  keypress_t key;

  key_reset(&key);

  while ((ch = getch())) {

    if (27 == ch && 0 == in_sequence) { // first int of a sequence
      in_sequence = 1;
      sequence[i++] = ch;

      continue;
    } else if (1 == in_sequence && 91 == ch) { // second int of a sequence

      sequence[i++] = ch;
      continue;

    } else if (1 == in_sequence) { // actual int sequence

      switch (ch) {
        case 65: key.name = "up"; break;
        case 66: key.name = "down"; break;
        case 67: key.name = "right"; break;
        case 68: key.name = "left"; break;
        default: continue;
      }

      sequence[i++] = ch;
      in_sequence = 0;

    } else if ('\n' == ch) {

      key.name = "enter";

    } else if ('\t' == ch) {

      key.name = "tab";

    } else if (' ' == ch) {

      key.name = "space";

    } else if ('\b' == ch || 0x7f == ch) {

      key.name = "backspace";

    }

    in_sequence = 0;

    if (NULL == key.name) {
      key.name = (char *)&ch;
    }

    rc = cb(ch, &key);
    if (-1 == rc) {
      break;
    }
    key_reset(&key);
    usleep(1000);

    // a sequence is no longer
    // than 3 parts
    if (i > 2) {
      i = 0;
    }
  }
}

static void
key_reset (keypress_t *key) {
  key->name = NULL;
//  key->meta = 0;
//  key->shift = 0;
//  key->ctrl = 0;
//  key->arrow = 0;
}

#endif

