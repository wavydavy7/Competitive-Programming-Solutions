#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N, M;
const int MX = 200001;
map<int, vector<int>> tr;
vector<int> deg(MX, 0);
vector<vector<LL>> dp(MX, vector<LL>(3, 0));
LL mod = 998244353;

void modadd(LL &a, LL b){
    a = (a + b) % mod;
}

void dfs(int v){
    int lf = 1;
    for (auto x : tr[v]){
        lf = 0;
        dfs(x);
    }
    if (lf) dp[v][2] = 1;
    else {
        dp[v][0] = 1;
        vector<LL> aux(3, 0);
        for (auto c : tr[v]){
            aux[0] = aux[1] = aux[2] = 0;
            modadd(aux[0], dp[v][0] * dp[c][0] % mod); //it's not part of a partition 
            modadd(aux[1], dp[v][0] * dp[c][1] % mod); //it's part of a partition, needs to be connected above
            modadd(aux[0], dp[v][0] * dp[c][2] % mod); //not used for something, but used below 
            modadd(aux[1], dp[v][0] * dp[c][2] % mod); //not used, but might be used to continue 

            modadd(aux[1], dp[v][1] * dp[c][0] % mod); //something below might try to continue
            modadd(aux[2], dp[v][1] * dp[c][1] % mod); //something might connect to finish
            modadd(aux[1], dp[v][1] * dp[c][2] % mod); //something might try and extend
            modadd(aux[2], dp[v][1] * dp[c][2] % mod); //something else might try to finish 

            modadd(aux[2], dp[v][2] * dp[c][0] % mod); //something might be extra
            modadd(aux[2], dp[v][2] * dp[c][1] % mod); //something might be used to finish
            modadd(aux[2], dp[v][2] * dp[c][2] % mod); //if there is something that's both finished, they can be combined 
            modadd(aux[2], dp[v][2] * dp[c][2] % mod); 
            swap(dp[v], aux);
        }
    }
}
//0 is none, 1 is above and below, 2 is only below 
int main(){
    cin >> N;
    for (int i = 1; i < N; i++){
        int p; 
        cin >> p;
        deg[p--]++;
        tr[p].pb(i);
    }
    dfs(0);
    cout << (dp[0][0] + dp[0][2]) % mod;
}