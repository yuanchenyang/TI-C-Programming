#define SAVE_SCREEN         // this directive forces saving/restoring the screen
#define USE_TI89
#define OPTIMIZE_ROM_CALLS
#define XCONST 80
#define YCONST 50


#include <tigcclib.h>


typedef struct Point {
  int x;
  int y;
  int z;  
} Point;

typedef struct Line {
  Point *p1;
  Point *p2;
} Line;

Point *pointBuf[100];
Line *lineBuf[100];
int pb = 0;
int lb = 0;
float rot[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

void drawPoint();

Point *makePoint(int x, int y, int z) {
  Point * const p = (Point * ) malloc(sizeof(Point));
  p->x = x;
  p->y = y;
  p->z = z;
  return p;
}

void addPoint(int x, int y, int z) {  
  pointBuf[pb++] = makePoint(x, y, z);
}

void DrawLineFast(short x1, short y1, short x2, short y2) {
  short x = x1, y = y1;
  short dx = abs (x2 - x1), dy = abs (y2 - y1);
  short ystep = (y1 < y2) ? 1 : -1, pystep = 30 * ystep;
  short mov = dx ? 0 : -1;
  unsigned char *ptr = (char*)LCD_MEM + 30 * y + (x >> 3);
  short mask = 1 << (~x & 7);
  if (x1 < x2)
    while (x != x2 || y != y2)
      {
        *ptr |= mask;
        if (mov < 0) y += ystep, ptr += pystep, mov += dx;
        else
          {
            mov -= dy;
            if (++x & 7) mask >>= 1;
            else ptr++, mask = 0x80;
          }
      }
  else
    while (x != x2 || y != y2)
      {
        *ptr |= mask;
        if (mov < 0) y += ystep, ptr += pystep, mov += dx;
        else
          {
            mov -= dy;
            if (x-- & 7) mask <<= 1;
            else ptr--, mask = 1;
          }
      }
}

void renderPoints() {
  int i;
  for (i = 0; i < pb; ++i) {
    drawPoint(pointBuf[pb]);
  }  
}

void drawPoint(Point *p) {
  int x = p->x;
  int y = p->y;
  int z = p->z;
  int x1 = (int) (x * rot[0][0] + y * rot[1][0] + z * rot[2][0]) + XCONST;
  int y1 = (int) (x * rot[0][1] + y * rot[1][1] + z * rot[2][1]) + YCONST;
  printf("(%i, %i, %i, %i, %i)", x1, y1, x, y, z);
  DrawPix(x1, y1, A_NORMAL);
}

void printMat(float mat[3][3]) {
  int x, y;
  for (y = 0; y < 3; ++y) {    
    printf("%f %f %f \n", mat[0][y], mat[1][y], mat[2][y]);
  }
}

_main() {
  clrscr();
  // addPoint(0, 0, 0);
  // addPoint(1, 0, 0);
  // addPoint(0, 1, 0);
  // addPoint(5, 5, 0);
  // renderPoints();
  // printMat(rot);
  pointBuf[0] = makePoint(0, 0, 0);
  pointBuf[1] = makePoint(20, 0, 0);
  pointBuf[2] = makePoint(0, 20, 0);
  pointBuf[3] = makePoint(20, 20, 0);
  renderPoints();
  ngetchx();
}


