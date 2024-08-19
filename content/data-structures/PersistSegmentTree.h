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

int iv = 0, ip = 0;
struct Node{
  Node *l, *r; int v, p=ip, le, ri;
  Node(int le, int ri, int v=iv, int p=ip, Node*l=0, Node*r=0)
    : l(l), r(r), v(v), p(p), le(le), ri(ri) {}
  Node(Node *l, Node *r)
    : l(l), r(r), v(l->v+r->v), le(l->le), ri(r->ri) {}
  void push(){
    int m = (le+ri)/2;
    if(!l) l = new Node(le, m), r = new Node(m+1, ri);
    if(p!=ip) l=l->update(le,m,p), r=r->update(m+1,ri,p), p=ip;
  }
  Node* update(int lq, int rq, int x){
    if(lq > ri || rq < le) return this;
    if(lq <= le && ri <= rq)
      return new Node(le, ri, v+x*(ri-le+1), p+x, l, r);
    push();
    return new Node(l->update(lq,rq,x), r->update(lq,rq,x));
  }
  int query(int lq, int rq){
    if(lq > ri || rq < le) return iv;
    if(lq <= le && ri <= rq) return v;
    push();
    return l->query(lq, rq) + r->query(lq, rq);
  }
};
Node* build(vi &a, int l, int r){
  if(l == r) return new Node(l, l, a[l]);
  int m = (l+r)/2;
  return new Node(build(a, l, m), build(a, m+1, r));
}
