#define SAVE_SCREEN         // this directive forces saving/restoring the screen

#define USE_TI89            // produce all types of files

#include <stdio.h>          // standard ANSI C input/output support
#include <kbd.h>            // keyboard handling support, needed for ngetchx
#include <args.h>

int match(char *regexp, char *text)
{
  if (regexp[0] == '^')
    return matchhere(regexp+1, text);
  do {    /* must look even if string is empty */
    if (matchhere(regexp, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
  if (regexp[0] == '\0')
    return 1;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp+2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
    return matchhere(regexp+1, text+1);
  return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
  do {    /* a * matches zero or more instances */
    if (matchhere(regexp, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;  
}

int _main(void)            // main entry point is function _main
{
  
  clrscr();                // clear the screen and reset print position
  int m;
  char regex[100], str[100];
  do {
    printf("Input string for matching:\n");
    scanf("%s", &str);
    printf("\nInput regex:\n");
    scanf("%s", &regex);
    m = match(regex, str);
    if (m == 0) {
      printf("\nNo match!\n");
    } else {
      printf("\nMatch!\n");
    }
    printf("Press any key to try again, ESC to cancel.\n");
    
  } while (ngetchx() != KEY_ESC);
  
  /*
  clrscr();
  ESI argptr;  
  int argtype;
  int m;
    
  InitArgPtr(argptr);  
  if (ArgCount() != 2) {
    printf ("Need two arguments!\n");
    ngetchx();
    return;
  }
  // char* regex = GetStrnArg (argptr);
  // char* str = GetStrnArg (argptr);
  
  m = match("", "");
  
  if (m == 0) {
    printf ("Match!\n");
  } else {
    printf ("No match!\n");
  }
  ngetchx();
  return 123;
  */
}
