#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 400010;

// Global arrays for 28 segment trees (for letters 'a' to 'z')
int s[28][N];   // s[q][x] stores the sum for letter q at node x.
char v[28][N];  // what this range was updated with 
char p[28][N];  // p[q][x] is 1 if there is a lazy update pending at node x.

// Global pointers used to select the current letter's arrays.
int *ss;
char *vv, *pp;

// Update the segment tree for letter q.
// x: current node (1-indexed), covering interval [l, r] (0-indexed).
// We want to update the subinterval [ll, rr] to value t (0 or 1).
void modify(int q, int x, int l, int r, int ll, int rr, int t) {
    if (l >= ll && r <= rr) {
        vv[x] = t;
        pp[x] = 1;
        ss[x] = t * (r - l + 1);
        return;
    }
    // Push lazy update down if needed.
    if (pp[x]) {
        vv[x+x]   = vv[x+x+1] = vv[x];
        pp[x+x]   = pp[x+x+1] = 1;
        if (!vv[x])
            ss[x+x] = ss[x+x+1] = 0;
        else {
            ss[x+x]   = (((l + r) >> 1) - l + 1);
            ss[x+x+1] = (r - ((l + r) >> 1));
        }
        pp[x] = 0;
    }
    int mid = (l + r) >> 1;
    if (ll <= mid)
        modify(q, x+x, l, mid, ll, rr, t);
    if (rr > mid)
        modify(q, x+x+1, mid+1, r, ll, rr, t);
    ss[x] = ss[x+x] + ss[x+x+1];
}

// Query the segment tree for letter q; returns the sum over interval [ll, rr].
int findsum(int q, int x, int l, int r, int ll, int rr) {
    if (l >= ll && r <= rr)
        return ss[x];
    if (pp[x]) {
        vv[x+x]   = vv[x+x+1] = vv[x];
        pp[x+x]   = pp[x+x+1] = 1;
        if (!vv[x])
            ss[x+x] = ss[x+x+1] = 0;
        else {
            ss[x+x]   = (((l + r) >> 1) - l + 1);
            ss[x+x+1] = (r - ((l + r) >> 1));
        }
        pp[x] = 0;
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (ll <= mid)
        res += findsum(q, x+x, l, mid, ll, rr);
    if (rr > mid)
        res += findsum(q, x+x+1, mid+1, r, ll, rr);
    ss[x] = ss[x+x] + ss[x+x+1];
    return res;
}

int n, m, i, lo, hi, cnt[255];
char c, st[N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d %d", &n, &m);
    scanf("%s", st);
    
    // Initialize each letter's segment tree.
    for (i = 0; i < n; i++) {
        int letter = st[i] - 'a';
        pp = p[letter];
        vv = v[letter];
        ss = s[letter];
        modify(letter, 1, 0, n - 1, i, i, 1);
    }
    
    // Process each query.
    while (m--) {
        scanf("%d %d", &lo, &hi);
        lo--; hi--;  // convert to 0-indexed
        char bad = ' ';
        
        // Count frequency of each letter in [lo, hi].
        for (c = 'a'; c <= 'z'; c++) {
            int letter = c - 'a';
            pp = p[letter];
            vv = v[letter];
            ss = s[letter];
            cnt[c] = findsum(letter, 1, 0, n - 1, lo, hi);
            if (cnt[c] & 1) {
                if (bad == ' ')
                    bad = c;
                else { bad = '!'; break; }
            }
        }
        if (bad == '!')
            continue;
        
        int oldlo = lo, oldhi = hi;
        // For each letter, clear the segment and then update left/right halves.
        for (c = 'a'; c <= 'z'; c++) {
            int letter = c - 'a';
            if (cnt[c] > 0) {
                pp = p[letter];
                vv = v[letter];
                ss = s[letter];
                modify(letter, 1, 0, n - 1, oldlo, oldhi, 0);
                int u = cnt[c] / 2;
                if (!u)
                    continue;
                modify(letter, 1, 0, n - 1, lo, lo + u - 1, 1);
                lo += u;
                modify(letter, 1, 0, n - 1, hi - u + 1, hi, 1);
                hi -= u;
            }
        }
        // If there is a letter with an odd count, update the middle.
        if (bad != ' ') {
            int letter = bad - 'a';
            pp = p[letter];
            vv = v[letter];
            ss = s[letter];
            modify(letter, 1, 0, n - 1, lo, hi, 1);
        }
    }
    
    // Reconstruct the final string.
    memset(st, 0, sizeof(st));
    for (c = 'a'; c <= 'z'; c++) {
        int letter = c - 'a';
        pp = p[letter];
        vv = v[letter];
        ss = s[letter];
        for (i = 0; i < n; i++) {
            if (!st[i] && findsum(letter, 1, 0, n - 1, i, i) == 1)
                st[i] = c;
        }
    }
    
    for (i = 0; i < n; i++)
        putchar(st[i]);
    printf("\n");
    
    return 0;
}
