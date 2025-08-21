#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<int> perm(n + 1);
    vector<int> pos(n + 1); 

    for (int i = 0; i < n; i++) {
        cin >> perm[i]; // values in [1..n]
        pos[perm[i]] = i;
    }
    

    vector<int> arr(m + 1);
    for (int i = 0; i < m; i++){
        cin >> arr[i]; // values in [1..n]
    }
    // seen[x] = last index where we saw the value x in arr
    // Must be of size n+1 to handle x = n
    vector<int> seen(n + 1, -1);
    vector<int> latest(m + 1, -1);

    for (int i = 0; i < m; i++) {
        // Update where we see arr[i]
        seen[arr[i]] = i;
        if (seen[perm[(pos[arr[i]] + n - 1) % n]] != -1) {
            latest[i] = seen[perm[(pos[arr[i]] + n - 1) % n]];
        }
    }
    int lim = 0;
    while ((1 << lim) <= n) {
        lim++;
    }
    // Build jump table
    vector<vector<int>> jump(m + 1, vector<int>(lim + 1, -1));
    vector<int> psum(m, -1);
    
    for (int i = 0; i < m; i++){
        jump[i][0] = latest[i];
    }
    for (int i = 1; i < lim; i++){
        for (int idx = 0; idx < m; idx++){
            if (jump[idx][i - 1] != -1)
            jump[idx][i] = jump[jump[idx][i - 1]][i - 1];
        }
    }
    //we need to populate first 
    for (int i = 0; i < m; i++) {
        int idx = i;
        int steps = n - 1;
        for (int bit = 0; bit < lim; bit++){
            if ((1 << bit) & steps && idx != -1){
                idx = jump[idx][bit];
            }
        }
        psum[i] = max(idx, psum[(i + m - 1) % m]);
    }

    // Answer queries
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--; 
        if (l <= psum[r]) cout << 1;
        else cout << 0;
    }
    return 0;
}
