#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 1e6 + 1;
int N;

template<class T> T invGeneral(T a, T b) {
    a %= b; 
    if (a == 0) return (b == 1 ? 0 : -1); 
    T x = invGeneral(b, a); 
    return (x == -1 ? -1 : ((1 - (ll)b * x) / a + b) % b);
}

template<class T> struct modInt {
    T val;
    modInt(T v = 0) { 
        val = v % MOD; 
        if (val < 0) val += MOD; 
    }
    modInt operator+(const modInt &other) const { return modInt(val + other.val); }
    modInt operator-(const modInt &other) const { return modInt(val - other.val + MOD); }
    modInt operator*(const modInt &other) const { return modInt(1LL * val * other.val % MOD); }
    modInt operator/(const modInt &other) const { return *this * modInt(invGeneral(other.val, MOD)); }
    friend ostream& operator<<(ostream &os, const modInt &x) { return os << x.val; }
};

typedef modInt<int> mi;
mi dp[MX][21][2];
// vector<vector<mi>> f(21, vector<mi>(21, 0));
int f(int x,int y)
{
    int tmp=(1<<x);
    if (y)
    tmp*=3;
    return N/tmp;
}

int main(){
    cin >> N;
    int p = 0;
    while ((1 << p) <= N) p++;
    p--;

    dp[1][p][0] = 1;
    if ((1 << (p - 1)) * 3 <= N) {
        dp[1][p - 1][1] = 1;
    }

    // for (int i = 0; i < 21; i++){
    //     for (int j = 0; j < 2; j++){
    //         f[i][j] = N / ((1 << i) * ((j == 1) ? 3 : 1));
    //     }
    // }

    for (int i = 1; i < N; i++){
        for (int x = 0; x <= p; x++){
            for (int y = 0; y < 2; y++){
                dp[i + 1][x][y] = dp[i + 1][x][y] + dp[i][x][y] * (f(x, y) - i);
                if (x > 0) dp[i + 1][x - 1][y] = dp[i + 1][x - 1][y] + dp[i][x][y] * (f(x-1, y) - f(x, y));
                if (y > 0) dp[i + 1][x][y - 1] = dp[i + 1][x][y - 1] + dp[i][x][y] * (f(x, y - 1) - f(x, y));
            }
        }
    }
    cout << dp[N][0][0];
    return 0;
}
