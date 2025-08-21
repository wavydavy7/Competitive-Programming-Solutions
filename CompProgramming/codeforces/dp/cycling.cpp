#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll max(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main(){
    int t; cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        //make a line container 
        //check boundary conditions, overflows, etc.
        LineContainer lines;
        vector<pair<ll, ll>> st;
        for (int i = 0; i < n; i++){
            //we need to add mx + b
            while (!st.empty() && a[i] < a[st.back().first]){ //the first is the min value
                st.pop_back();
            }
            ll diff;
            if (!st.empty()){
                diff = st.back().second + 1LL*(i - st.back().first)*(a[i] + 1) - 1;
            }
            else{
                diff = 1LL * (i + 1) * a[i] + (i + 1) - 1;
            }
            st.push_back({i, diff});
            //now, we need to find the minimum to some value, plus 
            lines.add(-(a[i] + 2), -(-i * (a[i] + 2) * 1LL + st.back().second)); //we need to add n at the end
            cout << -lines.max(i) << (i == (n - 1) ? "\n" : " ");
        }
    }        
}
