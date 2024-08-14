/**
 * Author: codicon
 * Date: 2024-07-22
 * License: NA
 * Source: Original
 * Description:
 * For problems asking for $\min$/$\max$ cost using $k$ or $\leq k$ 'groups'.
 * Replaces the groups state of the DP with a binary search.
 * Let $f(x)$ be the best cost using $x$ groups. $f(x)$ must be convex/concave.
 * Ensure $\max(\|f(x) - f(x-1)\|) \leq \max(\|l\|, \|r\|)$: almost guaranteed for \texttt{gen\_eq=0}.
 * \texttt{gen\_eq=0} is:
 * convex(nonincreasing $=k$ / general $\leq k$),
 * concave(nondecreasing $=k$ / general $\leq k$).
 * \texttt{gen\_eq=1} is: convex/concave(general $=k$).
 * Fill out \texttt{best}: add \texttt{+lambda} extra cost for each group
 * and return $\min \{\text{cost}, \text{groups}\}$ for convex, $\max$ for concave.
 * If \texttt{gen\_eq=1} and $n \cdot \max(\|f(x)-f(x-1)\|) > 4 \cdot 10^{18}$,
 * remove \texttt{/n} + use \texttt{\_\_int128} cost.
 * Time:
 * $O(\log(10^{18}) / N)$
 * Status:
 * convex(nonincreasing =k), concave(nondecreasing =k) tested on:
 * https://www.acmicpc.net/problem/12766
 * convex(general =k), concave(general =k) tested on:
 * https://www.acmicpc.net/problem/8653, https://www.acmicpc.net/problem/12766
 * convex(general <=k), concave(general <=k) tested on:
 * https://www.acmicpc.net/problem/17439
 * */
#pragma once

int n, k; // global
pii best(int lambda) { }
ll aliens_trick(bool convex, bool gen_eq=0) {
    ll l = gen_eq ? -4e18/n : -4e18*!convex;
    ll r = gen_eq ? 4e18/n : 4e18*convex;
    int sgn = convex ? 1 : -1;
    while (l < r) {
        ll m = l + (r-l)/2;
        sgn*best(m).S <= sgn*k ? r = m : l = m+1;
    }
    return best(r).F - r*k;
}
