#include <bits/stdc++.h>
using namespace std;

// Macros for convenience
#define pii pair<int, int>
#define pb push_back
#define f first
#define s second

// Constants
const int N = 4005;
const int K = 1000;
const int INF = 1e9;

// Global variables
int n, k;
int a[N][N];        // Input matrix
int cost[N][N];     // Cost matrix for cumulative sums
int dp[N][K];       // DP table for results

void solve(int le, int ri, int opt_l, int opt_r, int id) {
    if (le > ri) return;  // Base case: invalid range

    int mid = (le + ri) / 2;
    int best_cost = INF;
    int best_partition = -1;

    for (int i = opt_l; i <= min(opt_r, mid); i++) {
        int current_cost = dp[i - 1][id - 1] + cost[i][mid];
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_partition = i;
        }
    }

    dp[mid][id] = best_cost;  
    solve(le, mid - 1, opt_l, best_partition, id);
    solve(mid + 1, ri, best_partition, opt_r, id);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    
    cin >> n >> k;

    // Input matrix (1-based indexing)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    
    for (int j = 1; j <= n; j++) {
        cost[j][j] = 0;
        int sum = 0;
        for (int i = j - 1; i >= 1; i--) {
            sum += a[i][j];
            cost[i][j] = cost[i][j - 1] + sum;
        }
    }

    
    for (int i = 1; i <= n; i++) {
        dp[i][1] = cost[1][i];
    }


    for (int i = 2; i <= k; i++) {
        solve(1, n, 1, n, i);
    }

    
    cout << dp[n][k] << "\n";

    return 0;
}
