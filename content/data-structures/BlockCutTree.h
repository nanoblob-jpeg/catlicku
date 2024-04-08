/**
 * Author: usaco.guide
 * Date: ??
 * License: NA
 * Description: Returns block-cut tree of graph. vvi here is vector<vector<int>>
 * Time: $O(n)$.
 */
#pragma once
vvi bctree(vvi &g, vector<bool> &cutp, vi &id) {
  int n = (int)g.size(), timer = 0;
  vvi comps; vi stk, num(n), low(n);
  cutp.resize(n); id.resize(n);
  function<void(int,int,int&)>dfs=[&](int no,int p,int &t){
    num[no] = low[no] = ++t; stk.push_back(no);
    for (int son : g[no]) {
      if (son == p) continue;
      if (num[son]) low[no] = min(low[no], num[son]);
      else {
        dfs(son, no, t); low[no] = min(low[no], low[son]);
        if (low[son] >= num[no]){
          cutp[no] = (num[no]>1 || num[son]>2);
          comps.push_back({no});
          while (comps.back().back() != son) {
            comps.back().push_back(stk.back());
            stk.pop_back();
  } } } } };
  dfs(0, -1, timer);;
  function<vector<vector<int>>()> build_tree = [&]() {
    vvi t(1); int no_id = 0;
    for (int no = 0; no < n; no++)
      if(cutp[no]){id[no]=no_id++; t.push_back({});}
    for (auto &comp : comps) {
      int no = no_id++; t.push_back({});
      for (int u : comp)
        if (!cutp[u]) id[u] = no;
        else {
          t[no].push_back(id[u]);
          t[id[u]].push_back(no);
        } } return t; };
  return build_tree();
}
