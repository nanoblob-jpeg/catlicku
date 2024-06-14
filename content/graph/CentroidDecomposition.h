/**
 * Author: USACO Guide
 * Date: 2024-04-08
 * License: N/A
 * Source: https://usaco.guide/plat/centroid?lang=cpp
 * Description: $O(\log(n))$ depth. Builds into cent.
 * $\text{path}(u, v) = \text{path}(u, w) + \text{path}(w, v)$
 * , $w = \text{lca}(u, v)$ in centroid decomposition.
 * Usage: \texttt{initialize adj/cent; build(cent,root);}
 * Time: $O(n \log n)$
 */

vector<vi> adj;
vector<bool> rem(size(adj)); vi sub(size(adj));
int dfs_s(int c, int p = -1) {
    sub[c] = 1;
    for (int ch: adj[c]) {
        if (ch == p || rem[ch]) continue;
        sub[c] += dfs_s(ch, c);
    }
    return sub[c];
}
int get_c(int c, int n, int p = -1) {
    for (int ch: adj[c]) {
        if (ch == p || rem[ch]) continue;
        if (sub[ch] * 2 > n) return get_c(ch, n, c);
    }
    return c;
}
int build(vector<vi> &cent, int c = 0) {
    int cen = get_c(c, dfs_s(c)); // do something
    rem[cen] = true;
    for (int ch: adj[centroid]) {
        if(not rem[ch])cent[cen].push_back(build(cent, ch));
    }
    return cen;
}
