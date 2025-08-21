#include <bits/stdc++.h>
// #include "debug.h"
#define LL long long
#define pb push_back
using namespace std;
int N;
string s;
int mod = 1e9 + 7;

int main(){
    map<int, int> dp;
    cin >> N;
    vector<int> nums(N, 0);
    int l = 0;
    int e = 0;
    for (int i = 0; i < N; i++){
        cin >> nums[i];
    }
    for (int i = 0; i < N; i++){
         //earliest available does not work
        int val = nums[i];
        dp[val] = 1 + dp[val - 1];
        if (dp[val] > l) {
            l = dp[val];
            e = val;
        }
    }
    vector<int> res;
    cout << l << endl;
    for (int i = N - 1; i >= 0; i--){
        if (nums[i] == e){
            e--;
            res.pb(i);
        }
    }
    reverse(res.begin(), res.end());
    for (auto elem : res){
        cout << elem + 1 << " ";
    }
}