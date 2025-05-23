#include <stdio.h>
#include <math.h>

#define MAX_REFS 1000
#define EPS 1e-9

#define PI 3.14159265358979323846

typedef double DBL;

typedef struct
{
  DBL X, Y;
} POINT;

DBL DistToSeg( POINT P, POINT A, POINT B )
{
  DBL dx = B.X - A.X;
  DBL dy = B.Y - A.Y;
  DBL t;
  POINT proj;

  if (fabs(dx) < EPS && fabs(dy) < EPS)
    return _hypot(P.X - A.X, P.Y - A.Y);

  t = ((P.X - A.X) * dx + (P.Y - A.Y) * dy) / (dx * dx + dy * dy);

  if (t < 0.0)
    t = 0.0;
  else if (t > 1.0)
    t = 1.0;

  proj.X = A.X + t * dx;
  proj.Y = A.Y + t * dy;
  return _hypot(P.X - proj.X, P.Y - proj.Y);
}

int SimRay( DBL A, DBL B, DBL L, DBL X, DBL Y,
            DBL R, DBL Alpha, int MaxRefs )
{
  DBL alpha_rad = Alpha * PI / 180.0;
  POINT pos = {L, 0};
  POINT dir = {cos(alpha_rad), sin(alpha_rad)};
  POINT center = {X, Y};
  int refs = 0;

  while (refs <= MaxRefs)
  {
    DBL tx = dir.X > 0 ? (A - pos.X) / dir.X : (0 - pos.X) / dir.X;
    DBL ty = dir.Y > 0 ? (B - pos.Y) / dir.Y : (0 - pos.Y) / dir.Y;
    DBL t = tx < ty ? tx : ty;

    POINT next_pos = {pos.X + dir.X * t, pos.Y + dir.Y * t};

    if (DistToSeg(center, pos, next_pos) <= R + EPS)
      return refs;

    if (fabs(t - tx) < EPS)
      dir.X = -dir.X;
    if (fabs(t - ty) < EPS)
      dir.Y = -dir.Y;

    pos = next_pos;
    refs++;
  }

  return -1;
}

void main( void )
{
  DBL a, b, l, x, y, R, alpha;
  int res;

  printf("Enter 'a': ");
  scanf("%lf", &a);
  printf("Enter 'b': ");
  scanf("%lf", &b);
  printf("Enter 'l': ");
  scanf("%lf", &l);
  printf("Enter 'x': ");
  scanf("%lf", &x);
  printf("Enter 'y': ");
  scanf("%lf", &y);
  printf("Enter 'R': ");
  scanf("%lf", &R);
  printf("Enter 'alpha' (in degrees): ");
  scanf("%lf", &alpha);
  printf("\n");

  res = SimRay(a, b, l, x, y, R, alpha, MAX_REFS);

  if (res == -1)
    printf("Will never intersect the circle.\n");
  else
    printf("Will intersect the circle after %d reflection(s).\n", res);

  getchar();
  getchar();
}