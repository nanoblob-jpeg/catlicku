/**
 * Author: HoMaMaOvO (Riku Kawasaki, Masaki Nishimoto, Yui Hosaka)
 * Date: 2024
 * License: Unknown
 * Source: https://contest.ucup.ac/submission/269631
 * Description: alpha is [OS, OS+SIZE), sentinel (OSET-1)
 * no[0]: len 0(null in nxt), node[1]: len -1, node[2, nodLen] pali str
 * ts[pos,pos+len] pre/suff when created, fail: longest proper pali
 * quick[a]: longes proper pre/suff followed/preceded by a
 * nos->nodes, noLen->nodeLength,his->history,OSET/OS->OFFSET
 */
#pragma once
template <class T, int SIZE, T OSET> struct Depam {
  struct Node {int len, pos, fail, nxt[SIZE], quick[SIZE];};
  int noLen, pre, suf, nL, nR, l, r, hisLen;
  vector<Node>nos;vector<T>tsBuffer;T*ts;vector<pii>his;
  // curr whole str: ts[l, r)  (-nL <= l <= 0 <= r <= nR)
  //ts->((~pre)/suf before pushF/B, par of made node or -1)
  void setNode(Node &g, int l, int p, int f){
    g.len=l,g.pos=p,g.fail=f;memset(g.nxt,0,sizeof(g.nxt));}
  Depam(int nL_, int nR_) : nL(nL_), nR(nR_) {
    noLen = 2; hisLen = l = r = pre = suf = 0;
    nos.resize(2 + nL + nR); his.resize(nL + nR);
    setNode(nos[0],0,0,1); setNode(nos[1],-1,0,1);
    rep(a,0,SIZE) nos[0].quick[a]=nos[1].quick[a] = 1;
    tsBuffer.assign(1 + nL + nR + 1, OSET - 1);
    ts = tsBuffer.data() + (1 + nL);}
  const Node &operator[](int u) const {return nos[u];}
  void pushFront(T t) {
    const int a=t-OSET;his[hisLen++]={~pre, -1};ts[--l]=t;
    if (ts[l+1+nos[pre].len]!=t) pre=nos[pre].quick[a];
    Node &f = nos[pre];if (!f.nxt[a]) {
      his[hisLen-1].S = pre;Node &g=nos[noLen];
      setNode(g,f.len+2,l,nos[f.quick[a]].nxt[a]);
      memcpy(g.quick, nos[g.fail].quick, sizeof(g.quick));
      g.quick[ts[l + nos[g.fail].len] - OSET] = g.fail;
      f.nxt[a]=noLen++;/*needs to be after setting g.fail*/}
    if (nos[pre = f.nxt[a]].len == r - l) suf = pre;}
  void pushBack(T t) {
    const int a=t-OSET;his[hisLen++]={suf,-1};ts[r++]=t;
    if(ts[r-2-nos[suf].len]!=t)suf=nos[suf].quick[a];
    Node &f = nos[suf];if (!f.nxt[a]) {
      his[hisLen-1].S = suf;Node &g=nos[noLen];
      setNode(g,f.len+2,r-g.len,nos[f.quick[a]].nxt[a]);
      memcpy(g.quick, nos[g.fail].quick, sizeof(g.quick));
      g.quick[ts[r - 1 - nos[g.fail].len] - OSET] = g.fail;
      f.nxt[a]=noLen++;/*needs to be after setting g.fail*/}
    if (nos[suf = f.nxt[a]].len == r - l) pre = suf;}
  void undo() {
    const pii h = his[--hisLen];if (h.F < 0) {//pF
      if(nos[pre].len==r-l)suf=nos[suf].fail;
      pre=~h.F;if(~h.S){--noLen;nos[h.S].nxt[ts[l]-OSET]=0;}
      ts[l++]=OSET-1;}else{/*pB*/if(nos[suf].len==r-l)
      pre=nos[pre].fail;suf=h.F;if(~h.S){--noLen;
      nos[h.S].nxt[ts[r-1]-OSET]=0;}ts[--r]=OSET-1;}}};
