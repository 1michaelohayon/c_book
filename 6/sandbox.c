#include <math.h>
#include <stdio.h>
#define XMAX 700
#define YMAX 500

struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};

int main() {
  struct point pt = {10, 20};

  double dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);
  printf("x:%d, y:%d d\n", pt.x, pt.y);
  printf("dist %f\n", dist);

  //============================================
  struct rect screen;
  struct point middle;
  struct point makepoint(int, int), addpoint(struct point, struct point);

  screen.pt1 = makepoint(0, 0);
  screen.pt2 = makepoint(XMAX, YMAX);

  struct point pt3 = addpoint(makepoint(7, 15), screen.pt2);

  printf("pt1: %d, %d pt3: %d %d\n", screen.pt1.x, screen.pt1.y, pt3.x, pt3.y);

  return 0;
}
/* make a point from x and y componenets */
struct point makepoint(int x, int y) {
  struct point temp;
  temp.x = x;
  temp.y = y;
  return temp;
}

/* add two points */
struct point addpoint(struct point p1, struct point p2) {
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

/* return 1 if p in r, 0 if not */
int pinrect(struct point p, struct rect r) {
  return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}
