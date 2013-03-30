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
double vars[26];

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
    printf("%c", curr);
    buf[0] = (char)curr;
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

char get_lower_letter() {
  printf("Store to: ");
  char c;
  do {
    c = ngetchx();
  } while (! islowerletter(c));
  return c;
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
    printerror("Stack Overflow!\n");
  else
    numstack[++sp] = f;
}

double pop() {
  if (sp == 0) {
    return 0;
  }
  return numstack[sp--];
}

double peek() {
  return numstack[sp];
}
 
_main()
{
  struct token t;
  double temp;
  char c;
  clrscr();
  while ((t = get_token()).type != EXIT) {
    // printf("Char: %i\nNumber: %f", t.character, t.number); 
    // ngetchx();
    message[0] = '\0';
    if (t.type == NUMBER) 
      push(t.number);
    else if (islowerletter(t.character))
      push(vars[t.character - 'a']);
    else {
      switch (t.character) {
      case KEY_STO:
        c = get_lower_letter();
        vars[c - 'a'] = pop();
        break;
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
          printerror("Cannot divide by zero\n");
          push(temp);
        } else {
          push(pop() / temp);
        }        
        break;
      case '^':
        temp = pop();
        push(pow(pop(), temp));
        break;
      case KEY_PI:
        push(PI);
        break;
      case KEY_EXP:
        push(exp(1));
        break;
      case KEY_LN:
        push(log(pop()));
        break;
      case KEY_SIN:
        push(sin(pop()));
        break;
      case KEY_COS:
        push(cos(pop()));
        break;
      case KEY_TAN:
        push(tan(pop()));
        break;
      case KEY_ARCSIN:
        push(asin(pop()));
        break;
      case KEY_ARCCOS:
        push(acos(pop()));
        break;
      case KEY_ARCTAN:
        push(atan(pop()));
        break;
      case KEY_SQRT:
        push(sqrt(pop()));
        break;        
      }      
    }
    clrscr();
    printstack();
    printf("%s", message);
  }
}
