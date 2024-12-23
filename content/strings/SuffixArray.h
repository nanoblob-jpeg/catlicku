/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{lcp(i, j)} returns $lcp(s[i..], s[j..])$ in $O(1)$.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{alcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * $\texttt{alcp[i]} = lcp(\texttt{sa[i]}, \texttt{sa[i-1]})$, \texttt{alcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Can remove RMQ.h if you don't need lcp().
 * Time: O(n \log n) to construct, O(1) for lcp.
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct SuffixArray {
  vi sa, alcp, rsa;
  RMQ<int> st;
  SuffixArray(string& s, int lim=256) { // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
    x.push_back(0), sa = alcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i,0,n) ws[x[i]]++;
      rep(i,1,lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    rep(i,1,n) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; alcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
           s[i + k] == s[j + k]; k++);
    rsa = rank;
    st = RMQ<int>(alcp);
  }
  // lcp(s[i..], s[j..])
  int lcp(int i, int j) {
      if (i == j) return size(sa)-1 - i;
      i = rsa[i], j = rsa[j]; if (i > j) swap(i, j);
      return st.query(i+1, j+1);
  }
};
