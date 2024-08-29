/**
 * Author: Czaj Nik
 * Date: ????
 * License: N/A
 * Description: \texttt{set<int>} implemented with bitsets.
 *  \texttt{IntSet<(int)1e9>} = 125MB. 20x faster than \texttt{set<int>} (50-200e6 ops = 1s).
 * Status: Tested on yosupo judge
 */
#pragma once

template<int n> struct IntSet {
  static constexpr int b = 64;
  uint64_t v[n/b + 1] = {};
  IntSet<(n < b+1 ? 0 : n/b + 1)> up;
  bool contains(int i) { return (v[i/b] >> i%b) & 1; }
  void ins(int i){if(!v[i/b])up.ins(i/b); v[i/b] |= 1ull<<i%b;}
  void era(int i) {if (!(v[i/b] &= ~(1ull<<i%b))) up.era(i/b);}
  int next(int i) { auto x = v[i/b] >> i%b;      // j > i or -1
    if (x &= ~1) return i + __builtin_ctzll(x);
    return (i = up.next(i/b)) < 0 ? i :
           i*b + __builtin_ctzll(v[i]); }
  int prev(int i) { auto x = v[i/b] << (b-i%b-1);// j < i or -1
    if (x &= INT64_MAX) return i - __builtin_clzll(x);
    return (i = up.prev(i/b)) < 0 ? i :
           i*b + b-1-__builtin_clzll(v[i]); } };
template<> struct IntSet<0> { void ins(int) {} void era(int) {}
  int next(int) { return -1; } int prev(int) { return -1; } };
