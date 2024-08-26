/**
 * Author: Jerry Li
 * Date: 2024-08-16
 * License: CC0
 * Source: me
 * Description: Persistent, Implicit, and Lazy segment tree.
 * Can add to large intervals and compute sum of intervals.
 * Can be modified (e.g. set + max). iv is the default value, ip is default prop value. 
 * Bounds are inclusive on BOTH sides: [lq, rq].
 * High constant factor: 1e5 ops = (200ms, 300MB). Use bump allocator to 2x speed.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(0, sz(v)-1); or Node* tr = build(v, 0, sz(v)-1);
 * Status:
 * Tested on: 
 * 1. https://cses.fi/problemset/task/1737/
 *      code: https://cses.fi/paste/b41710a7ef34dcd49c362c/
 * 2. https://atcoder.jp/contests/abc253/tasks/abc253_f
 *      code: https://atcoder.jp/contests/abc253/submissions/56885117
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
  Node* update(int lq, int rq, int x){ // [lq, rq]
    if(lq > ri || rq < le) return this;
    if(lq <= le && ri <= rq)
      return new Node(le, ri, v+x*(ri-le+1), p+x, l, r);
    push();
    return new Node(l->update(lq,rq,x), r->update(lq,rq,x));
  }
  int query(int lq, int rq){ // [lq, rq]
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
