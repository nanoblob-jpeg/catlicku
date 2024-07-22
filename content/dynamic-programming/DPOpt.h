/**
 * Author: indy256
 * Date: ??
 * License: NA
 * Source: https://codeforces.com/blog/entry/8219
 * Description:
 * A[i][j] is smallest k that gives OPT ans, ie dp[i][j] = dp[i-1][k]+C[k][j]
 * C[i][j] is cost function
 */
#pragma once

void ConvexHull(){
/* Orig recurrence: dp[i] = min_{j<i}+b[j]*a[i]
 * To apply: b[j] >= b[j+1] && a[i] <= a[i+1]
 * view dp state as line with slope b[j] and y-int of dp[j]
 * define convex hull of these and find best ans.*/
}
void DnQOpt(){
/* Orig recurrence:dp[i][j] = min_{k<j}(dp[i-1][k]+C[k][j])
 * to apply: A[i][j] <= a[i][j+1]
 * opt from O(kn^2) to O(knlogn)
 * compute(d,L,R,optL,optR) denote compute dp[d][L...R]
 * where we know k must be in optL...optR
 * 1) special case: L==R, end of our recur
 * 2) let M = (L+R)/2, solve dp[d][M] as well as opt[d][M]
 * 3) compute(d, L, M-1, optL, opt[d][M])
 * 4) compute(d, M+1, R, opt[d][M], optR)*/
}
void KnuthOpt2(){
/* O rec:dp[i][j] = min_{i<=k<j}(dp[i][k]+dp[k][j]+C[i][j])
 * opt from O(n^3) to O(n^2)
 * to apply, A[i][j-1] <= A[i][j] <= A[i+1][j] or
 *   C[a][c]+C[b][d]<=C[a][d]+C[b][c] and C[b][c]<=C[a][d]*/
  for(int i{}; i < n; ++i) opt[i][i]=?;
  for(int i=n-2;i>=0;--i){for(int j=i+1;j<n;++j){
    int mn=INT_MAX, cost=C(i, j);
    for(int k=opt[i][j-1];k<=min(j-1,opt[i+1][j]);++k){
        if(mn>=dp[i][k]+dp[k+1][j]+cost){
            opt[i][j]=k; mn=dp[i][j]+dp[k+1][j]+cost;}
    } dp[i][j]=mn;
  }}
}
