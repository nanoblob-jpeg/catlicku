/**
 * Author: Elijah Huang
 * Date: 2024-08-18
 * License: CC0
 * Source: me 
 * Description: 0-indexed sparse ($O(N\log N)$ memory) 2D segment tree.
 * Computes max a[xl,xr)[yl,yr) and sets single elements a[x][y].
 * Offline, so requires that the elements to be updated are known in advance.
 * Before all "real" updates: \texttt{fakeUpdate(all updates); init();}.
 * High constant factor: 1e5 ops = (1s, 80MB).
 * Time: $O(\log^2 N)$.
 * Status:
 * Tested on:
 * 1. https://www.acmicpc.net/problem/15977
 *      code: https://www.acmicpc.net/source/82681350
 */
#pragma once

#include "SegmentTree.h"

struct ST2 {
  int nx; ve<ve<pii>> pts; vector<ST> st;
  ST2(int nx) : nx(nx), pts(2*nx) {}
  void fakeUpdate(int x, int y) {
    for (int i = x+nx; i; i /= 2)
      pts[i].push_back({y, x});
  }
  void init() {
    for (auto &v: pts) sort(all(v)), st.emplace_back(sz(v));
  }
  int ind(int i, int y, int x) {
    return lower_bound(all(pts[i]),pii(y, x))-pts[i].begin();
  }
  void update(int x, int y, int v) { // a[x][y] = v
    for (int i = x+nx; i; i /= 2)
      st[i].update(ind(i, y, x), v);
  }
  int query(int xl, int xr, int yl, int yr) { // [xl,xr)[yl,yr)
    int r = iv;
    for (xl += nx, xr += nx; xl < xr; xl /= 2, xr /= 2) {
      if (xl % 2) r = f(r,
        st[xl].query(ind(xl, yl, 0), ind(xl, yr, 0))), xl++;
      if (xr % 2) r = f(r,
        st[--xr].query(ind(xr, yl, 0), ind(xr, yr, 0)));
    }
    return r;
  }
};
