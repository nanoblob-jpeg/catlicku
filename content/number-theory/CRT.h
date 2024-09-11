/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Returns $(x, \text{lcm}(m, n))$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$. Returns $(0, 0)$ if there is no solution.
 * Assumes $mn < 2^{62}$.
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ar<ll, 2> crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    if ((a - b) % g) return {};
    x = (b - a) % n * x % n / g * m + a;
    return {x < 0 ? x + m*n/g : x, m*n/g};
}
