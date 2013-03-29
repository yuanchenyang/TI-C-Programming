#define SAVE_SCREEN         // this directive forces saving/restoring the screen

#define USE_TI89            // produce all types of files

#include <stdio.h>          // standard ANSI C input/output support
#include <kbd.h>            // keyboard handling support, needed for ngetchx

void _main(void)            // main entry point is function _main
{
  clrscr ();                // clear the screen and reset print position
  double sum, v;
  sum = 0;
  while (scanf("%lf", &v) == 1)
    printf("\t%.2f\n", sum += v);
}
