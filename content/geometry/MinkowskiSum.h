/**
 * Author: Iván Renison
 * Date: 2024-07-30
 * License: CC0
 * Source: notebook el vasito
 * Description: Compute Minkowski sum of two strictly convex non empty polygons (i.e. two hulls).
 * Returns answer in CCW order.
 * The Minkowski sum of two polygons $$P$$ and $$Q$$ viewed as sets of $\mathbb{R}^2$ is defined as
 * $\{p + q : p \in P, q \in Q\}$
 * Time: O(n \log n + m \log m)
 * Status: stress-tested
*/

#include "Point.h"
#include "ConvexHull.h"
#include "sideOf.h"

typedef Point<ll> P;
void reorder(vector<P> &p){
  if (sideOf(p[0], p[1], p[2]) < 0) reverse(all(p));
  rotate(p.begin(), min_element(all(p)), p.end());
}
vector<P> minkowskiSum(vector<P> p, vector<P> q) {
  if (min(sz(p), sz(q)) < 3) {
    vector<P> v;
    for (P pp : p) for (P qq : q) v.push_back(pp + qq);
    return convexHull(v);
  }
  reorder(p), reorder(q);
  rep(i, 0, 2) p.push_back(p[i]), q.push_back(q[i]);
  vector<P> r;
  ll i = 0, j = 0;
  while (i + 2 < sz(p) || j + 2 < sz(q)) {
    r.push_back(p[i] + q[j]);
    ll cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
    i += cross >= 0, j += cross <= 0;
  }
  return r;
}
