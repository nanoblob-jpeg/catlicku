/**
 * Author: usaco.guide
 * Date: ??
 * License: NA
 * Description: Returns block-cut tree of graph.
 *  The block-cut tree has a node for each articulation point and each biconnected component.
 *  There is an edge between each biconnected component and articulation point it contains.
 *  Let $i$ be a node in the original graph.
 *  \texttt{artp[i] == true} means $i$ is an articulation point.
 *  \texttt{id[i]} is the node $i$ is a part of in the block-cut tree.
 *  Let \texttt{nartp = accumulate(all(artp), 0)},
 *  then nodes \texttt{0...nartp-1} are articulation points.
 *  Can pass \texttt{artp, id} with any contents.
 * Time: $O(n)$.
 * Status: Tested on https://www.acmicpc.net/problem/15768
 */
#pragma once

vvi blockCutTree(vvi& g, vector<bool>& artp, vi& id) {
  int n = sz(g), timer = 0;
  vvi comps; vi stk, num(n), low(n);
  artp.assign(n, 0); id.assign(n, 0);
  function<void(int,int,int&)> dfs = [&](int no,int p,int &t) {
    num[no] = low[no] = ++t; stk.push_back(no);
    for (int son : g[no]) {
      if (son == p) continue;
      if (num[son]) low[no] = min(low[no], num[son]);
      else {
        dfs(son, no, t); low[no] = min(low[no], low[son]);
        if (low[son] >= num[no]){
          artp[no] = (num[no]>1 || num[son]>2);
          comps.push_back({no});
          while (comps.back().back() != son) {
            comps.back().push_back(stk.back());
            stk.pop_back();
  } } } } };
  dfs(0, -1, timer);
  vvi t;
  rep(i, 0, n) if (artp[i]) t.push_back({}), id[i] = sz(t)-1;
  for (auto &comp : comps) {
    t.push_back({});
    for (int u : comp)
      if (!artp[u]) id[u] = sz(t)-1;
      else t[sz(t)-1].push_back(id[u]), t[id[u]].push_back(sz(t)-1);
  } 
  return t;
}
