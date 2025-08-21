#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 30001;
int N, D;
vector<int> gems(MX, 0);
vector<vector<int>> dp(MX, vector<int>(600, -1)); 

int dfs(int is, int j){
    if (is >= MX) return 0; 
    int jp = j - (D - 250); 
    if (dp[is][jp] != -1) return dp[is][jp];  

    int res = gems[is];  
    res = max(res, gems[is] + dfs(is + j, j));         
    res = max(res, gems[is] + dfs(is + j + 1, j + 1));  
    if (j > 1) res = max(res, gems[is] + dfs(is + j - 1, j - 1));  

    dp[is][jp] = res;  
    return res;
}

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);      

    cin >> N >> D;
    for (int i = 0; i < N; i++){
        int x;
        cin >> x;
        gems[x]++;
    }

    // Start DFS and print result
    cout << dfs(D, D);
    return 0;
}
