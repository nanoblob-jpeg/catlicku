/**
 * Author: Jerry
 * Date: 2024-03-27
 * License: Unknown
 * Source: Eertree - a powerful tool for dealing with palindromes
 * Description: Builds eertree for a string.
 * \texttt{p[i]} is the node for longest palindrome which
 * ends at $i$'th position in the string.
 * Time: O(n \log \alpha)
 */
#pragma once
struct enode{int len; enode *suf, *ne[26];
  enode(int l, enode *s=nullptr):len(l), suf(s){
    for(int i{}; i<26; ++i) ne[i] = nullptr;
  }
};
struct eertree{
  string s;
  enode *curr, *root, *iroot;
  vector<enode*> p;
  eertree(){
    iroot = new enode(-1),iroot->suf = iroot;
    root = new enode(0),root->suf = iroot;
    curr = root;
  }
  // returns true if new palindrome added
  bool append(char c){
    bool add{};s += c;enode *t = curr;int ind = s.size()-1;
    while(ind-1-t->len<0 || s[ind-1-t->len] != c)t=t->suf;
    if(!t->ne[c-'a']){
      enode *ne = t->ne[c-'a'] = new enode(t->len + 2);
      if(ne->len == 1)ne->suf = root;
      else{
        do t = t->suf;
        while(ind-1-t->len<0||s[ind-1-t->len]!=c);
        ne->suf = t->ne[c-'a'];
      }
      curr = ne, add = true;
    }else curr = t->ne[c-'a'];
    p.push_back(curr); return add;
  }
};
