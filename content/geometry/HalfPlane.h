/**
 * Author: xyz
 * Description: Computes the area of the intersection of a set of half-planes.
 *  Each half-plane \texttt{Line(s, e)} is represented as the area to the right of ray s->e.
 *  To return the actual intersection, make small edits.
 *  It will be a ccw convex polygon, but may have duplicate/collinear points.
 * Time: O(n \log n)
 * Status: Tested on https://www.acmicpc.net/problem/23194.
 *  Probably on a few problems by the original lgm team.
 */

#include "Point.h"
#include "lineIntersection.h"

#define eps 1e-8  // check > ~sqrt(2)*error(lineInter) ?
typedef Point<double> P;
struct Line {
  P s, e; // Right of ray s -> e
  explicit Line(P s = P(), P e = P()) : s(s), e(e) {};
  P intpo(Line y) { return lineInter(s, e, y.s, y.e).S; }
  P dir() { return e - s; }
  bool contains(P x) { return (e - s).cross(x - s) < eps; }
  bool out(P x) { return !contains(x); }
};
bool mycmp(P a, P b) {
  if (a.x * b.x < 0) return a.x < 0;
  if (abs(a.x) < eps) {
    if (abs(b.x) < eps) return a.y > 0 && b.y < 0;
    return b.x < 0 ? a.y > 0 : 1;
  }
  if (abs(b.x) < eps) return a.x < 0 ? b.y < 0 : 0;
  return a.cross(b) > 0;
}
double halfPlaneIntersectionArea(ve<Line> b) {
  sort(all(b), [&](Line &a, Line &b)
    { return mycmp(a.dir(), b.dir()); });
  int n = sz(b), q = 1, h = 0;
  ve<Line> c(all(b) + 10);
  rep(i, 0, n) {
    while (q < h && b[i].out(c[h].intpo(c[h - 1]))) h--;
    while (q < h && b[i].out(c[q].intpo(c[q + 1]))) q++;
    c[++h] = b[i];
    if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps)
      if (c[h].dir().dot(c[h - 1].dir()) > 0) { h--;
        if (b[i].out(c[h].s)) c[h] = b[i];
      } else return 0; // 0 or infinity, bounding box => 0
  }
  while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1]))) h--;
  while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1]))) q++;
  if (h - q <= 1) return 0; // Intersection is empty
  c[h + 1] = c[q];
  ve<P> s; // s is the intersection as a ccw convex polygon
  rep(i, q, h+1) s.push_back(c[i].intpo(c[i + 1]));
  double area = s.back().cross(s[0]);
  rep(i, 0, sz(s)-1) area += s[i].cross(s[i + 1]);
  return area / 2;
}
