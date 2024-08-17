/**
 * Author: Jerry Li
 * Date: 2024-08-16
 * License: CC0
 * Source: me
 * Description: Persistent segment tree with ability to add values of large intervals, and compute sum of intervals.
 * Can be changed to other things. iv is the default value, pv is default prop value. 
 * Time: O(\log N).
 * Usage: Node* tr = new Node(0, sz(v)-1); or Node* tr = build(v, 0, sz(v)-1);
 * Status: stress-tested a bit
 */
#pragma once

int iv = 0, pv = 0;
struct Node{
  Node*l = 0, *r=0; int val, prop, le = 0, ri = -1;
  Node()=delete;
  Node(int a,int b,int c=iv,int d=pv,Node*nl=0, Node*nr=0){
    l = nl,r = nr,val = c,prop = d,le = a,ri = b;}
  void push(int mid){
    l=l->update(prop,le,mid);r=r->update(prop,mid+1,ri);
    val = l->val+r->val; prop = pv;
  }
  Node* update(int amt, int lq, int rq){
    if(le > ri || lq > ri || rq < le) return this;
    else if(lq <= le && ri <= rq)
      return new Node(le, ri, val+amt*(ri-le+1), prop+amt, l, r);
    else{
      int mid = le + (ri-le)/2;
      if(!l) l = new Node(le, mid);
      if(!r) r = new Node(mid+1, ri);
      if(prop != pv) push(mid);
      Node*nl=l->update(amt,lq,rq),*nr=r->update(amt,lq,rq);
      return new Node(le, ri, nl->val+nr->val, pv, nl, nr);
  } }
  int query(int lq, int rq){
    if(le > ri || lq > ri || rq < le) return iv;
    else if(lq <= le && ri <= rq) return val;
    else{
      int mid = le + (ri-le)/2;
      if(!l) l = new Node(le, mid);
      if(!r) r = new Node(mid+1, ri);
      if(prop != pv) push(mid);
      return l->query(lq, rq) + r->query(lq, rq);
  } }
};
Node* build(vi &a, int l, int r){
    if(l == r) return new Node(l, l, a[l]);
    int mid = l + (r-l)/2;
    Node*nl = build(a, l, mid), *nr = build(a, mid+1, r);
    return new Node(l, r, nl->val+nr->val, pv, nl, nr);
}
