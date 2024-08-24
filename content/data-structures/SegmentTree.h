/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree.
 * Can be changed by modifying \texttt{iv}, \texttt{f}.
 * Low constant factor: 1e6 ops = 150ms (2x faster than recursive).
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

int iv = INT_MIN;
int f(int a, int b) { return max(a, b); } // commutative

struct ST {
  vector<int> s; int n;
  ST(int n = 0) : s(2*n, iv), n(n) {}
  void update(int i, int v) { // a[i] = v
    for (s[i += n] = v; i /= 2;)
      s[i] = f(s[i * 2], s[i * 2 + 1]);
  }
  int query(int b, int e) { // query [b, e)
    int r = iv;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) r = f(r, s[b++]);
      if (e % 2) r = f(s[--e], r);
    }
    return r;
  }
};
