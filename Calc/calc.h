#define MAXINPUT 100
#define MAXSTACK 20
#define MAXMESSAGE 100

#define NUMBER 0
#define CHARACTER 1
#define EXIT 2

#define KEY_PI 140
#define KEY_EXP 16472
#define KEY_LN 4184
#define KEY_SIN 4185
#define KEY_COS 4186
#define KEY_TAN 4180
#define KEY_ARCSIN 16473
#define KEY_ARCCOS 16474
#define KEY_ARCTAN 16468
#define KEY_SQRT 4138

#define isnumberc(c) ((c) >= '0' && (c) <= '9')
#define isnumberstart(c) (isnumberc(c) || (c) == KEY_SIGN || (c) == '.')
#define islowerletter(c) ((c) >= 'a' && (c) <= 'z')
#define printerror(m) strcpy(message, m)

