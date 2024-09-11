/**
 * Author: Unknown
 * Date: Unknown
 * Source: https://cp-algorithms.com/data_structures/treap.html
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/merges. 
 *  Can also insert, move and reverse ranges. Currently lazy.
 *  Remove push() and uncomment "..new Node.." for just persistent.
 *  For both, add method \texttt{t->update(prop) \{ return new Node(t + prop) \}}
 *  and use it to make push() create new nodes.
 *  1e5 (split/merge) = 25ms. 1e5 (move/reverse) = 150ms. 1e5 (lazy+persistent) = (500ms, 600MB).
 * Time: $O(\log N)$
 * Status: 
 *  1. Stress-tested
 *  2. https://cses.fi/problemset/task/2073/ (Lazy (Reverse), Insert)
 *       Code at https://cses.fi/paste/9026fe796244a1bc9cd6ae/
 *  3. https://cses.fi/problemset/task/2072/ (Move, Insert)
 *       Code at https://cses.fi/paste/157de824bcf64e839cd6d6/
 *  4. https://atcoder.jp/contests/abc253/tasks/abc253_f (Persistent + Lazy)
 *       Code at https://atcoder.jp/contests/abc253/submissions/56989219
 */
#pragma once

#define cnt(n) ((n) ? (n)->c : 0)
struct Node {
    Node *l = 0, *r = 0;
    int v, y, c = 1, rev = 0;
    Node(int v) : v(v), y(rand()) {}
    Node(Node *a) { *this = *a; }
    void pull() { c = cnt(l) + cnt(r) + 1; }
    void push() { 
        if (rev) { swap(l, r);
            if (l) l->rev ^= 1; if (r) r->rev ^= 1; rev = 0;
        }
    }
};
// l = [0, i), r = [i, n)
void split(Node* t, Node*& l, Node*& r, int i) {
    if (!t) { l = r = 0; return; }
    t->push(); // t = new Node(t);
    // Replace with comments for lower_bound(i)
    if (i <= cnt(t->l)/*x->v*/) split(t->l, l, t->l, i), r = t;
    else split(t->r, t->r, r, i - cnt(t->l) - 1 /*i*/), l = t;
    t->pull();
}
void merge(Node*& t, Node* l, Node* r) {
    if (!l || !r) t = l ? l : r;
    else if (l->y < r->y) {
        r->push(); // r = new Node(r);
        merge(r->l, l, r->l); t = r;
    }
    else {
        l->push(); // l = new Node(l);
        merge(l->r, l->r, r); t = l;
    }
    t->pull();
}
void insert(Node*& t, Node* n, int i) { // (0 indexed)
    Node *l, *r;
    split(t, l, r, i), merge(l, l, n), merge(t, l, r);
}
// Move [l, r] to index k (0 indexed)
void move(Node*& t, int l, int r, int k) {
    Node *a, *b, *c;
    split(t, a, c, r+1), split(a, a, b, l), merge(t, a, c);
    if (k<=l) insert(t, b, k);
    else insert(t, b, k - (r - l + 1) /*k*/);
}
// Reverse [l, r] (0 indexed)
void rev(Node*& t, int l, int r) {
    Node *a, *b, *c;
    split(t, a, c, r+1), split(a, a, b, l);
    b->rev ^= 1;
    merge(a, a, b), merge(t, a, c);
}
