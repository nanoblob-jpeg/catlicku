/**
 * Author: robert1003.github.io
 * Date: 2020-02-29
 * License: NA
 * Source: robert1003.github.io
 * Description: Solves $dp[j] = \min_{0 \leq i < j} (dp[i] + c(i+1, j))$
 * $c(i, j)$ must satisfy Quadrangle Inequality:
 * convex($c(b, d) - c(b, c) \leq c(a, d) - c(a, c)$) for all $a \leq b \leq c \leq d$.
 * For concave flip $\leq$ to $\geq$.
 * To use, fill out \texttt{c, f, T}.
 * Time: O(N \log N)
 * Status: Tested convex on https://www.acmicpc.net/problem/17439.
 */
#pragma once

struct Transition { int i, l, r; };
T knuth_convex(int n) {
  ve<T> dp(n+1);
  auto c = [&](int l, int r) -> ll {};  // 1 <= l <= r <= n
  auto f = [&](int i, int j) -> T {return dp[i] + c(i+1, j);};
  deque<Transition> dq = {{0, 1, n}};
  rep(i, 1, n+1) {
    dp[i] = f(dq.front().i, i);
    if (dq.front().r == i) dq.pop_front(); else dq.front().l++;
    while (sz(dq) && f(dq.back().i, dq.back().l)
                     >= f(i, dq.back().l)) dq.pop_back();
    if (!sz(dq)) dq.push_back({i, i+1, n});
    else {
      auto [pi, l, r] = dq.back();
      while (l < r) {
        int m = (l+r+1)/2;
        if (f(pi, m) >= f(i, m)) r = m-1;
        else l = m;
      }
      if ((dq.back().r=r) != n) dq.push_back({i, r+1, n});
    }
  }
  return dp[n];
}
T knuth_concave(int n) {
  ve<T> dp(n+1);
  auto c = [&](int l, int r) -> ll {};  // 1 <= l <= r <= n
  auto f = [&](int i, int j) -> T {return dp[i] + c(i+1, j);};
  stack<Transition> s; s.push({0, 1, n});
  rep(i, 1, n+1) {
    dp[i] = f(s.top().i, i);
    if (s.top().r == i) s.pop(); else s.top().l++;
    while (sz(s) && f(s.top().i, s.top().r)
                    > f(i, s.top().r)) s.pop();
    if (!sz(s)) s.push({i, i+1, n});
    else{
      auto [pi, l, r] = s.top();
      while (l < r){
        int m = (l+r)/2;
        if (f(pi, m) > f(i, m)) l = m+1;
        else r = m;
      }
      if ((s.top().l=l) != i+1) s.push({i, i+1, l-1});
    }
  }
  return dp[n];
}
