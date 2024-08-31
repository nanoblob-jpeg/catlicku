/**
 * Author: Krzysztof Potepa
 * Date: 2024
 * License: N/A
 * Description: Extended Li Chao tree, a lazy segment tree that maintains
 *  a sequence $c_0, c_1 \ldots c_{n - 1}$. Can point query $c_x$.
 *  Can range update $c(x) = (\max, \text{add})(c(x), f(x))$, $f$ is linear.
 *  However, can change to any $F$ that is a family of functions closed under function addition, 
 *  and $f \neq g \implies$ the functions intersect at one point.
 * Status: Tested on random stuff
 */
#pragma once

struct LiChao {
  struct Func { ll a, b; // a*x + b
    ll operator()(ll x) const { return a*x+b; }
    Func operator+(Func r) const { return {a+r.a, b+r.b}; } };
  static constexpr Func ID_ADD{0, 0}, ID_MAX{0, ll(-1e9)};
  ve<Func> v, p; int n;
  LiChao(int N = 0) { for (n = 1; n < N; n *= 2);
    v.resize(n*2, ID_MAX); p.resize(n*2, ID_ADD); }
  void push(int i) {
    if (i < n) rep(j, 0, 2) p[i*2+j] = p[i*2+j] + p[i],
      v[i*2+j] = v[i*2+j] + p[i]; p[i] = ID_ADD; }
  // For each x in [l,r), set c[x] = max(c[x], f(x))
  // O(log^2 n), O(log n) if [l,r) = [0,n)
  void max(int l, int r, Func f, int i=1, int b=0, int e=-1) {
    if (e<0) e=n; if (l >= e || b >= r || i >= n*2) return;
    int m = (b+e) / 2; push(i);
    if (b >= l && e <= r) { auto& g = v[i];
      if (g(m) < f(m)) swap(g, f);
      if (g(b) < f(b)) max(l, r, f, i*2, b, m);
      else max(l, r, f, i*2+1, m, e); }
    else max(l, r, f, i*2, b, m), max(l, r, f, i*2+1, m, e); }
  // For each x in [l,r), set c[x] = c[x] + f(x)
  // O(log^2 n), O(1) if [l,r) = [0,n)
  void add(int l, int r, Func f, int i=1, int b=0, int e=-1) {
    if (e < 0) e = n; if (l >= e || b >= r) return;
    if (b >= l && e <= r) p[i] = p[i] + f, v[i] = v[i] + f;
    else { int m = (b+e) / 2; push(i);
      max(b, m, v[i], i*2, b, m);
      max(m, e, v[i], i*2+1, m, e); v[i] = ID_MAX;
      add(l, r, f, i*2, b, m); add(l, r, f, i*2+1, m, e); } }
  // O(log n), get value of c[x]
  auto query(int x) { int i = x+n; auto ret = v[i](x);
    while (i /= 2) ret = ::max(ret+p[i](x), v[i](x));
    return ret; } };
