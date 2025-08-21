#include <bits/stdc++.h>
using namespace std;

using base = complex<double>;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
const double C_PI = acos(-1);
const int MAXN = 262144;

int r[MAXN][6];

// Bit-reversal FFT
void fft(vector<base>& a, bool invert) {
    int n = sz(a);
    for (int i = 0, j = 0; i < n; ++i) {
        if (i > j) swap(a[i], a[j]);
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * C_PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; j++) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

// Union-Find with Path Compression
int root(int x, int y) {
    return (y == r[x][y]) ? y : (r[x][y] = root(x, r[x][y]));
}

int main() {
    char in1[MAXN], in2[MAXN];
    scanf("%s %s", in1, in2);

    int N = strlen(in1), M = strlen(in2), i, j, k;
    
    // Initialize root array
    for (i = 0; i <= N - M; i++) for (j = 0; j < 6; j++) r[i][j] = j;

    // FFT preprocessing for in1
    vector<base> vch1[6], vch2[6];
    for (i = 0; i < 6; i++) {
        vector<int> Vu(MAXN, 0);
        for (j = 0; j < N; j++) if (in1[j] == 'a' + i) Vu[j] = 1;
        vector<base> vch(all(Vu));
        fft(vch, false);
        vch1[i] = vch;
    }

    // FFT preprocessing for in2
    for (i = 0; i < 6; i++) {
        vector<int> Vu(MAXN, 0);
        for (j = 0; j < M; j++) if (in2[j] == 'a' + i) Vu[M - 1 - j] = 1;  // Reverse pattern
        vector<base> vch(all(Vu));
        fft(vch, false);
        vch2[i] = vch;
    }

    // Multiply and inverse FFT
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            vector<base> vch(MAXN);
            for (k = 0; k < MAXN; k++) vch[k] = vch1[i][k] * vch2[j][k];
            fft(vch, true);

            // Process convolution results
            for (k = 0; k <= N - M; k++) {
                int t = (int)(vch[k + M - 1].real() + (vch[k + M - 1].real() > 0 ? 0.5 : -0.5));
                if (t != 0) {
                    r[k][root(k, i)] = root(k, j);
                }
            }
        }
    }

    // Output result
    for (i = 0; i <= N - M; i++) {
        int ans = 6;
        for (j = 0; j < 6; j++) if (r[i][j] == j) ans--;
        printf("%d ", ans);
    }
    
    return 0;
}
