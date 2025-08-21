#include <bits/stdc++.h>
#include "debug.h"
using namespace std;
#define pb push_back
typedef long long ll;
const int MOD = 1e9 + 7;
const int MX = 300000;
int N, K;

int main(){
    int n = 10;
    vector<int> fact(n + 1, 1);
    vector<int> bn(n, 0);
    for (int i = 1; i < n; i++){
        fact[i + 1] = (i + 1) * fact[i];
    }

    bn[0] = 1;
    bn[1] = 1;
    for (int i = 1; i < n; i++){
        for (int j = 0; j <= i; j++){
            bn[i + 1] += (fact[i] / (fact[j]*fact[i - j])) * bn[i - j];
            debug(i);
            debug(bn[i]);
        }
    }
    debug(bn);



    
}