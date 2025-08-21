#include <bits/stdc++.h>
#define ll long long
using namespace std;
int N; 
int mod = 998244353;

//Complementary counting, next permutation
int modsub(int a, int b) {
    int diff = (a - b) % mod;
    if (diff < 0) diff += mod;
    return diff;
}


ll modexp(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    cin >> N;
    ll fact[N + 1];
    fact[0] = 1;

    for (int i = 1; i <= N; i++) {
        fact[i] = (i * fact[i - 1]) % mod;
    }

    ll ans = (N * fact[N]) % mod;

    for (int i = 1; i < N; i++) {
        ll inv_fact_i = modexp(fact[i], mod - 2, mod); // Modular inverse of fact[i]
        ans = modsub(ans, (fact[N] * inv_fact_i) % mod);
    }

    cout << ans;
}