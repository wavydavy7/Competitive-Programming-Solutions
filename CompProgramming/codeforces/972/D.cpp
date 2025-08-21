#include <bits/stdc++.h>
#include "../../algo/debug.h"
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

void solve() {
    int n;
    std::cin >> n;
    
    int ans = 0;
    i64 cnt = 0;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<int> prea(n + 1), preb(n + 1), sufa(n + 1), sufb(n + 1);
    for (int i = 0; i < n; i++) {
        prea[i + 1] = std::gcd(prea[i], a[i]);
        preb[i + 1] = std::gcd(preb[i], b[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        sufa[i] = std::gcd(sufa[i + 1], a[i]);
        sufb[i] = std::gcd(sufb[i + 1], b[i]);
    }
    
    std::vector<std::array<int, 2>> fa {{0, 0}}, fb {{0, 0}};
    std::vector<std::array<int, 2>> pa, pb;
    for (int i = 0; i <= n; i++) {
        if (i == n || prea[i] != prea[i + 1]) {
            pa.push_back({prea[i], i}); //register when it changes
        }
        if (i == n || preb[i] != preb[i + 1]) {
            pb.push_back({preb[i], i});
        }
    }
    // debug(pa);
    // debug(pb);
    for (int r = 1; r <= n; r++) {
        int t = a[r - 1];
        for (int i = fa.size() - 1; i >= 0; i--) {
            t = std::gcd(t, fa[i][0]);
            fa[i][0] = t;
        }
        t = b[r - 1];
        for (int i = fb.size() - 1; i >= 0; i--) {
            t = std::gcd(t, fb[i][0]);
            fb[i][0] = t;
        }
        int k = 0;
        for (int i = 0; i < fa.size(); i++) {
            if (k > 0 && fa[k - 1][0] == fa[i][0]) {
                fa[k - 1][1] = fa[i][1];
            } else {
                fa[k] = fa[i];
                k++;
            }
        }
        fa.resize(k);
        
        k = 0;
        for (int i = 0; i < fb.size(); i++) {
            if (k > 0 && fb[k - 1][0] == fb[i][0]) {
                fb[k - 1][1] = fb[i][1];
            } else {
                fb[k] = fb[i];
                k++;
            }
        }
        fb.resize(k);
        
        fa.push_back({0, r});
        fb.push_back({0, r});
        debug(r);
        debug(fa);
        debug(fb);
        int ipa = 0, ipb = 0, ifa = 0, ifb = 0;
        int lst = -1;
        while (true) {
            int u = std::min({pa[ipa][1], pb[ipb][1], fa[ifa][1], fb[ifb][1]});
            if (u >= r) {
                break;
            }
            if (u > lst) {
                int res = std::gcd(pa[ipa][0], std::gcd(fb[ifb][0], sufa[r])) + std::gcd(pb[ipb][0], std::gcd(fa[ifa][0], sufb[r]));
                if (res > ans) {
                    ans = res;
                    cnt = u - lst;
                } else if (res == ans) {
                    cnt += u - lst;
                }
            }
            lst = u;
            if (pa[ipa][1] == u) {
                ipa++;
            }
            if (pb[ipb][1] == u) {
                ipb++;
            }
            if (fa[ifa][1] == u) {
                ifa++;
            }
            if (fb[ifb][1] == u) {
                ifb++;
            }
        }
    }
    std::cout << ans << " " << cnt << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}