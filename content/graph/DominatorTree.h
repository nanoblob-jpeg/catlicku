/**
 * Author: Tanuj Khattar
 * Date: 2016-01-11
 * License: N/A
 * Source: https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
 * Description: Given a directed graph, we say $b$ is a dominator of $a$
 * if all paths $1 \to a$ go through $b$.
 * Dominator tree satisfies:
 * ($b$ is an ancestor of $a$) $\Longleftrightarrow$ ($b$ is a dominator of $a$)
 * Usage: \texttt{initialize adj 1 indexed; build();}
 * Time: $O((n+m) \cdot \log(n))$
 */

const int N=0; vi adj[N];
vi dom_tree[N], rg[N], buc[N];
int sdom[N], par[N], dom[N], dsu[N], lab[N], ar[N], rev[N], T;
int Find(int u, int x=0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = Find(dsu[u], x+1);
    if (v < 0) return u;
    if (sdom[lab[dsu[u]]] < sdom[lab[u]]) lab[u] = lab[dsu[u]];
    dsu[u] = v;
    return x ? v : lab[u];
}
void Union(int u, int v) { dsu[v] = u; }
void dfs0(int u) {
    ar[u]=++T; rev[T]=u; lab[T]=T; sdom[T]=T; dsu[T]=T;
    for (int w: adj[u]) {
        if (!ar[w]) dfs0(w), par[ar[w]]=ar[u];
        rg[ar[w]].push_back(ar[u]);
    }
}
void build() {
    dfs0(1);
    for (int i = T; i >= 1; i--) {
        for (int j = 0; j < sz(rg[i]); j++)
            sdom[i] = min(sdom[i], sdom[Find(rg[i][j])]);
        if (i > 1) buc[sdom[i]].push_back(i);
        for (int w : buc[i]) {
            int v = Find(w);
            if (sdom[v] == sdom[w]) dom[w] = sdom[w];
            else dom[w] = v;
        }
        if (i > 1) Union(par[i], i);
    }
    for (int i = 2; i <= T; i++) {
        if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        dom_tree[rev[dom[i]]].push_back(rev[i]);
    }
}
