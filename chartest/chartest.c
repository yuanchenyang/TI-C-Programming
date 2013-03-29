#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89

#include <kbd.h>            // keyboard handling support, needed for ngetchx
#include <stdio.h>

_main()
{
  clrscr();
  short c;
  while ((c = ngetchx()) != KEY_ESC) {
    printf("Char Code: %i\n", c);
  }
}
