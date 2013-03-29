#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89

#include <stdio.h>
#include <kbd.h>
#include <timath.h>
#include <string.h>
#include "calc.h"

struct token {
  int type;
  short character;
  double number;
};

double numstack[MAXSTACK];
int sp = 0;
char message[MAXMESSAGE];

int isnumberc(char c) {
  return (c >= '0') && (c <= '9');
}

int isnumberstart(short c) { 
  return isnumberc(c) || c == KEY_SIGN ; // number or negative
}

struct token get_token() {
  char buf[MAXINPUT];
  short curr;
  int dots = 0;
  struct token t;
  
  printf("> ");
  curr = ngetchx();
  if (curr == KEY_ESC) {
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

/* sp points to the topmost entry on the stack. The first entry on the stack is
   always 0 and cannot be popped. */

void push(double f) {
  if (sp + 1 >= MAXSTACK)
    strcpy(message, "Stack Overflow!\n");
  else
    numstack[++sp] = f;
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
    clrscr();
    message[0] = '\0';
    if (t.type == NUMBER) {
      push(t.number);
    } else {
      switch (t.character) {
      case KEY_BACKSPACE:
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
          strcpy(message, "Cannot divide by zero\n");
          push(temp);
        } else {
          push(pop() / temp);
        }        
        break;
      case '^':
        temp = pop();
        push(pow(pop(), temp));
      }      
    }    
    printstack();
    printf("%s", message);
  }
}
