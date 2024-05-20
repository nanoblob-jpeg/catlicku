/**
 * Author: Jerry Li
 * Date: 2024-04-01
 * License: NA
 * Description: Counts num elements in range equal to q, kth smallest, or range count. All indicies are 0 indexed and inclusive on both ides
 * Time: Operations are O(log alpha).
 * Status: Stress-tested
 */
#pragma once
struct wavelet{
  struct node{
    int l, r; vector<int> val, mr; node *le{}, *ri{};
    node(int lv, int rv, vector<int> &a):l(lv), r(rv){
      for(int i : a) val.push_back(i);}
    node(int lv, int rv):l(lv), r(rv){}};
  node *root;
  // l and r are min and max values
  wavelet(vector<int> &a, int l, int r){
    root = new node(l, r, a); build(root);}
  void build(node *no){
    if(no->l == no->r) return;
    int m = no->l + (no->r-no->l)/2, run{};
    no->le=new node(no->l, m); no->ri=new node(m+1, no->r);
    for(int i : no->val){
      if(i <= m) no->le->val.push_back(i);
      else no->ri->val.push_back(i), run++;
      no->mr.push_back(run); }
    build(no->le); build(no->ri);
  }
  int count(int r, int q){
    node *no = root;
    while(no->l != no->r){
      if(r < 0) return 0;
      int m = no->l + (no->r-no->l)/2;
      if(q <= m) r = r-no->mr[r], no = no->le;
      else r = no->mr[r]-1, no = no->ri;
    } return r+1;
  }
  int count(int l, int r, int q){
    return count(r, q) - count(l-1, q);
  }
  // gets kth smallest element in a[l, r]
  // return -1 if there is none
  int kth(int l, int r, int k){
    if(k <= 0 || k > r-l+1) return -1;
      node *no = root;
      while(no->l != no->r){
        int c=r-no->mr[r]+1-(l==0?0:l-1-no->mr[l-1]+1);
        if(k <= c){
          l = l == 0 ? 0 : l-1-no->mr[l-1]+1;
          r = r-no->mr[r]; no = no->le;
        }else{
          l = (l == 0 ? 0 : no->mr[l-1]);
          r = no->mr[r]-1; k -= c; no = no->ri;
        }} return no->l;
  }
  // counts l <= i <= r and x <= a[i] <= y
  int rc(int l, int r, int x, int y, node *o=nullptr){
    if(!o) return rc(l, r, x, y, root);
    if(l > r || o->l > y || o->r < x) return 0;
    if(x <= o->l && o->r <= y) return r-l+1;
    return rc(l==0?0:l-1-o->mr[l-1]+1,r-o->mr[r],x,y,o->le)
      +rc(l==0?0:o->mr[l-1],o->mr[r]-1,x,y,o->ri);
  }
  void swap(int i, node *no = nullptr){
    if(!no){swap(i, root); return;}
    if(no->l==no->r || i==(int)no->mr.size()-1) return;
    int m = no->l + (no->r-no->l)/2;
    std::swap(no->val[i], no->val[i+1]);
    if(no->mr[i]-(i == 0 ? 0 : no->mr[i-1])){
      if(no->mr[i+1]-no->mr[i])swap(no->mr[i]-1, no->ri);
      else no->mr[i]--;
    }else{
      if(no->mr[i+1] - no->mr[i])no->mr[i]++;
      else swap(i-no->mr[i], no->le);}
  }
};

