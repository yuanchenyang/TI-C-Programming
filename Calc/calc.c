#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89            // produce all types of files

#define MAXINPUT 100
#define MAXSTACK 100

#define NUMBER 0
#define CHARACTER 1
#define EXIT 2

#define ESC 8

#include <stdio.h>
#include <stdlib.h>
#include <kbd.h>            // keyboard handling support, needed for ngetchx

struct token {
  int type;
  char character;
  double number;
};

double numstack[MAXSTACK];
int sp = 0;

int isnumberc(char c) {
  return (c >= '0') && (c <= '9');
}

int isnumberstart(char c) { 
  return isnumberc(c) || c == -83 ; // number or negative
} 

struct token get_token() {
  char buf[MAXINPUT];
  char curr;
  int bufp = 0;
  int dots = 0;
  struct token t;
  
  printf("> ");
  buf[bufp++] = curr = getchar();
  if (curr == ESC) {
    t.type = EXIT;    
  } else if (isnumberstart(curr)) {
    while (1) {
      buf[bufp++] = curr = getchar();
      if (curr == '.' && dots == 0)
        dots++;
      else if (!isnumberc(curr))
        break;      
    }
    buf[bufp] = '\0';
    printf("%s", buf);
    t.type = NUMBER;
    t.number = atof(buf);
  } else {
    t.type = CHARACTER;
    t.character = curr;    
  }
  printf("\n");
  return t;
}

void printstack() {
  int i;
  for (i = 1; i <= sp; ++i) {
    printf ("%.12g\n", numstack[i]);
  }
}

void push(double f) {
  if (sp++ >= MAXSTACK)
    printf("Stack Overflow!\n");
  numstack[sp] = f;
}

double pop() {
  if (sp == 0) {
    return 0;
  }
  return numstack[sp--];
}

_main()
{
  struct token t;
  double temp;
  clrscr();
  while ((t = get_token()).type != EXIT) {
    // printf("Char: %i\nNumber: %f", t.character, t.number); 
    // ngetchx(); 
    if (t.type == NUMBER) {
      push(t.number);
    } else {
      switch (t.character) {
      case '+':
        push(pop() + pop());
        break;
      case '-':
        temp = pop();
        push(pop() - temp);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        temp = pop();
        if (temp == 0) {
          printf("Cannot divide by zero!\n");
          push(temp);
        } else {
          push(pop() / temp);
        }        
        break;
      default:
        printf("Invalid character\n");
        break;
      }
    }
    clrscr();
    printstack();
  }
}
