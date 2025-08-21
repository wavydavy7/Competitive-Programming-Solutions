#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
#define pb push_back
using namespace std;
int N; 
int mod = 1e9 + 7;

int main(){
    cin >> N;
    vector<int> nums(N + 1, 0);
    int n;
    for (int i = 0; i < N; i++){
        cin >> n;
        nums[i] = n;
    }
    vector<int> dp(1e6 + 1, 0);
    dp[0] = 1;
    //dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]
    for (int i = 0; i < N; i++) { // Iterate over the array elements
        //you only need to iterate over the relevant ones
        vector<int> cur; 
        for (int j = 1; j * j <= nums[i]; j++){ 
            if (nums[i] % j == 0) {
                cur.pb(j);
                if (nums[i]/j != j) cur.pb(nums[i] / j);
            }  
        }
        sort(cur.begin(), cur.end());
        reverse(cur.begin(), cur.end());
        for (auto val : cur){
            dp[val] = (dp[val - 1] + dp[val]) % mod;
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) { // Sum up subsequences of all lengths
        ans = (ans + dp[i]) % mod;
    }

    cout << ans;
}

