#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N;
string s;
int mod = 1e9 + 7;

void modadd(int &a, int b){
    a = (a + b) % mod;
}
int main(){
    cin >> N >> s;
    int sl = s.length();
    vector<vector<vector<vector<int>>>> dp(2*N + 2, vector<vector<vector<int>>>(sl + 2, vector<vector<int>>(N + 2, vector<int>(2, 0))));
    vector<vector<int>> pi(sl + 1, vector<int>(2, 0));
    vector<int> tru(sl + 1, 0);

    pi[0][(s[0] == '(') ? 0 : 1] = 1;
    for (int i = 1; i < sl; i++){
        int j = tru[i - 1];
        int jo = tru[i - 1];
        int oth = (s[i] == '(') ? ')' : '(';
        while (j > 0 && s[i] != s[j]){
            j = tru[j - 1];
        }
        if (s[i] == s[j]) j++;
        tru[i] = j;
        
        
        while (jo > 0 && oth != s[jo]){
            jo = tru[jo - 1];
        }
        if (oth == s[jo]) jo++;
        int ins = jo;

        //now we do additional
        if (s[i] == '('){
            pi[i][0] = i + 1;
            pi[i][1] = ins;
        }
        else{
            pi[i][0] = ins;
            pi[i][1] = i + 1;
        }
    }
    //for the cycle around conditions 
    int j = tru[sl - 1];
    int j2 = tru[sl - 1];
    while (j > 0 && '(' != s[j]){
        j = tru[j - 1];
    }
    if ('(' == s[j]) j++;
    pi[sl][0] = j;

    while (j2 > 0 && ')' != s[j2]){
        j2 = tru[j2 - 1];
    }
    if (')' == s[j2]) j2++;
    pi[sl][1] = j2;
    // debug(pi);
    //prepare transitions
    dp[0][0][0][0] = 1;
    for (int i = 0; i < 2*N; i++){
        for (int mtc = 0; mtc <= sl; mtc++){
            for (int bal = 0; bal <= N; bal++){
                for (int add = 0; add < 2; add++){
                    if (bal + 1 <= N) modadd(dp[i + 1][pi[mtc][0]][bal + 1][(pi[mtc][0] == sl) | add], dp[i][mtc][bal][add]);
                    if (bal > 0) modadd(dp[i + 1][pi[mtc][1]][bal - 1][(pi[mtc][1] == sl) | add], dp[i][mtc][bal][add]);
                }
            }
        }
    }
    // debug(dp);
    int res = 0;
    for (int i = 0; i <= sl; i++){
        modadd(res, dp[2*N][i][0][1]);
    }
    cout << res;
}