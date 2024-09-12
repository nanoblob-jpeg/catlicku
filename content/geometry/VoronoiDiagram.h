/**
 * Author: Elijah Huang
 * Date: 2024-09-12
 * Source:
 * Description: Given points, returns map[$p$] = \{is\_inf, ccw\_voronoi\_region($p$)\} for each $p$ in points.
 *  is\_inf=true if the region is infinite, in which case the two rays will have length \texttt{INF}.
 *  There must be no duplicate points and they should not be all collinear.
 * Time: O(n \log n)
 * Status: Tested on https://www.acmicpc.net/problem/15695
 */
#pragma once

#include "FastDelaunay.h"

typedef Point<double> Pd;
map<P, pair<bool,ve<Pd>>> voronoi(ve<P>& pts, double INF=1e9) {
  ve<P> d = triangulate(pts); map<P, ve<P>> adj;
  for (int i = 0; i < sz(d); i += 3) rep(j, 0, 3) {
    P a = d[i+j], b = d[i+(j+1)%3];
    adj[a].push_back(b-a); adj[b].push_back(a-b); 
  }
  map<P, pair<bool,ve<Pd>>> v;
  auto c = [](P a) { return Pd(a.x, a.y); };
  for (auto &[p, a]: adj) {
    auto &[inf, b] = v[p];
    sort(all(a), [](P& a, P& b) {
      return pii(a.y < 0 || (a.y == 0 && a.x < 0), a.y * b.x)
        < pii(b.y < 0 || (b.y == 0 && b.x < 0), a.x * b.y); });
    a.erase(unique(all(a)), end(a)); int m = sz(a);
    rep(i, 0, m) if (a[(i+m-1)%m].cross(a[i]) <= 0)
      inf = 1, rotate(begin(a), begin(a)+i, end(a));
    rep(i, 0, m-inf) { 
      Pd d = c(a[(i+1)%m]), e = c(a[i]);
      b.push_back(
      c(p) + (d*e.dist2()-e*d.dist2()).perp()/d.cross(e)/2); 
    }
    if (inf)
      b.push_back(b[m-2] + c(a[m-1]).perp().unit() * INF),
      b.insert(begin(b), b[0] - c(a[0]).perp().unit() * INF);
  }
  return v;
}

