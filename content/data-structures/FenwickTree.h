/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0, i) and adds to single elements a[i].
 * Time: $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int i, ll x) { // a[i] += x
		for (; i < sz(s); i |= i + 1) s[i] += x;
	}
	ll query(int i) { // sum of values in [0, i)
		ll res = 0;
		for (; i > 0; i &= i - 1) res += s[i-1];
		return res;
	}
	int lower_bound(ll x) { // min i st sum of [0, i] >= x
		// Returns n if no sum is >= x, or -1 if empty sum is.
		if (x <= 0) return -1;
		int i = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (i + pw <= sz(s) && s[i + pw-1] < x)
				i += pw, x -= s[i-1];
		}
		return i;
	}
};
