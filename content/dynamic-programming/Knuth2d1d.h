/**
 * Author: Jerry Li
 * Description: (Array Merging) When doing DP on intervals:
 * $a[i][j] = \min_{i \le k < j}(a[i][k] + a[k+1][j]) + f(i, j)$.
 * (Array Partition) For min cost to split an array of length n into m partitions.
 * Need Quadrangle Inequality, $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$, and for array partition,
 * also need $f(b,c) \le f(a,d)$ for all $a \le b \le c \le d$.
 * \texttt{(i, j)} are 0 indexed.
 * Time: O(NM, N^2)
 * Status: Tested, verifiers(acmicpc.net/problem/13261 and 13974)
 */
#pragma once

int knuth_array_partition(int n, int m, F f){
  // dp[index][partition number]
  // f(i, j, k) = cost of [i, j] as the kth partition
  vvi dp(n+1, vi(m+1, 1e18)), opt(n+1, vi(m+1, n));
  dp[0][0] = opt[0][0] = 0;
  irep(i, n, 0) opt[i][1] = 0, dp[i][1] = f(0, i-1, 1);
  rep(j, 2, m+1) irep(i, n, 0)
    rep(k,opt[i][j-1],i==n?n+1:min(i+1, opt[i+1][j]+1))
      if(dp[i][j] >= dp[k][j-1] + f(k, i-1, j))
        dp[i][j]=dp[k][j-1]+f(k, i-1, j), opt[i][j] = k;
  return dp.back().back();
}
int knuth_array_merging(int n, F f){
  // dp[left bound][right bound], inclusive on both sides
  // f(i, j) calls to determine cost of [i, j]
  vvi dp(n, vi(n, 1e18)), opt(n, vi(n));
  rep(i, 0, n) dp[i][i] = f(i, i), opt[i][i] = i;
  irep(i, n-1, -1) rep(j, i+1, n)
    rep(k, opt[i][j-1], min(j-1, opt[i+1][j])+1)
      if(dp[i][j] >= dp[i][k] + dp[k+1][j] + f(i, j))
        dp[i][j]=dp[i][k]+dp[k+1][j]+f(i, j),opt[i][j] = k;
  return dp[0].back();
}
