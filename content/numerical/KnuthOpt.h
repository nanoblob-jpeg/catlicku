/**
 * Author: robert1003.github.io
 * Date: 2020-02-29
 * License: NA
 * Source: robert1003.github.io
 * Description: Optimizes dp of the form dp[j] = min(0<= i < j) f(i, j)
 * where f(i, j) is usually dp[i] + cost(i+1, j)/cost(i, j).
 * For a < b <= c < d
 * Monge Condition: Convex(f(a, c)+f(b, d) <= f(a, d) + f(b, c))
 * Totally Monotone: Convex(f(a, c) >= f(b, c) implies f(a, d) >= f(b, d))
 * For Concave flip <= to >= and vice versa. Monge implies totally monotone
 * Time: O(Nlog(N))
 */
#pragma once

struct Node{long long p, l, r;};
void KnuthConvex{
  deque<Node> dq; dp[0] = 0; dq.push_back({0, 1, n});
  for(int i{1}; i <= n; ++i){
    dp[i] = f(dq.front().p, i);
    if(dq.front().r==i)dq.pop_front(); else dq.front().l++;
    while(!dq.empty()&&f(i,dq.back().l)
      <f(dq.back().p,dq.back().l)) dq.pop_back();
    if(dq.empty()) dq.push_back({i, i+1, n});
    else{ int l = dq.back().l, r = dq.back().r;
      while(l < r){ int mid = r- (r-l)/2;
        if(f(i, mid) < f(dq.back().p, mid)) r = mid-1;
        else l = mid;} dq.back().r = l;
      if(l != n) dq.push_back({i, l+1, n});}}
}
void KnuthConcave{
  vector<Node> v; dp[0] = 0; v.push_back({0, 1, n});
  for(int i{1}; i <= n; ++i){
    dp[i] = f(v.back().p, i);
    if(v.back().r == i) v.pop_back(); else v.back().l++;
    while(!v.empty()&&f(i,v.back().r)
      <f(v.back().p,v.back().r)) v.pop_back();
    if(v.empty()) v.push_back({i, i+1, n});
    else{ int l = v.back().l, r = v.back().r;
      while(l < r){ int mid = l+ (r-l)/2;
        if(f(i, mid) < f(v.back().p, mid)) l = mid+1;
        else r = mid;} v.back().l = l;
      if(l != i+1) dq.push_back({i, i+1, l-1});}}
}
