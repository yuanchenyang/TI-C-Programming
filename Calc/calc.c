#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89            // produce all types of files

#include <stdio.h>
#include <kbd.h>            // keyboard handling support, needed for ngetchx
#include <timath.h>
#include "calc.h"

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
  return isnumberc(c) || c == NEG_SIGN ; // number or negative
} 

struct token get_token() {
  char buf[MAXINPUT];
  char curr;
  int dots = 0;
  struct token t;
  
  printf("> ");
  curr = getchar();
  if (curr == ESC) {
    t.type = EXIT;
  } else if (isnumberstart(curr)) {
    buf[0] = curr;
    getsn(&buf[1], MAXINPUT);
    float n = atof(buf);
    if (is_nan(n)) {
      t.type = CHARACTER;
      t.character = '\0';
    }
    else {
      t.type = NUMBER;
      t.number = n;
    }
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
      case BACKSPACE:
        pop();
        break;
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
          // Cannot divide by zero
          push(temp);
        } else {
          push(pop() / temp);
        }        
        break;
      case POWER:
        temp = pop();
        push(pow(pop(), temp));
      }      
    }
    clrscr();
    printstack();
  }
}
