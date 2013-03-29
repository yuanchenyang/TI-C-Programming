#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 100
#define MAXSTACK 100

#define NUMBER 0
#define CHARACTER 1
#define EXIT 2

#define KEY_ESC 27

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

struct token get_token() {
  char buf[MAXINPUT];
  char curr;
  int bufp = 0;
  int dots = 0;
  struct token t;
  
  printf("> ");
  buf[bufp++] = curr = getchar();
  if (curr == KEY_ESC) {
    t.type = EXIT;    
  } else if (isnumberc(curr)) {
    while (1) {
      buf[bufp++] = curr = getchar();
      if (curr == '.' && dots == 0)
        dots++;
      else if (!isnumber(curr))
        break;      
    }
    buf[bufp] = '\0';
    t.type = NUMBER;
    printf("%s\n", buf);
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

main()
{
  struct token t;
  double temp;

  while ((t = get_token()).type != EXIT) {
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
      }
    }    
    printstack();
  }
    
  return 0;
}
