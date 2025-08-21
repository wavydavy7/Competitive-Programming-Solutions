#include <bits/stdc++.h>
//#include "debug.h"
using namespace std;
#define ll long long


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int M = 4e6 + 1;
    vector<int> have(M + 1, 0);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        have[a[i]] = 1;
    }

    vector<int> post(M);
    vector<int> pre(M);
    post[M - 1] = -1;
    pre[0] = -1;
    for (int i = M - 2; i >= 0; i--){
        post[i] = have[i] ? i : post[i + 1];
    }
    for (int i = 1; i < M; i++){
        pre[i] = have[i] ? i : pre[i - 1];
    }

    //least k
    for (ll k = 1; ; k++){ //start at 1 because of perf squares
        //let's start here
        if (a[0] > k*k + k) continue;
        //max diff before 
        ll und = k;
        ll ov = max(0LL, a[0] - k*k);
        ll add = k * k - a[0];
        ll x = k;
        while (true){ //suppose for the edge case you don't move
            ll diff = x*(x + 1) + 1 - add; //smth that could be in the no zone after translated but before another 
            if (diff >= M) break; //must be significantly higher
            if (post[diff] != -1){//nothing after this 
                ov = max({ov, 0LL, x - (post[diff] - diff)}); //this is what you ought to do for some more
            }
            x++; //this is the least something has to be moved from there in order to get into position
        }
        x = k;
        while (true){ //the thing is, it might be moved too far
            ll diff = x*(x + 1) - add; //it's within the range 
            if (diff >= M) break;
            if (pre[diff] != -1){
                und = min(und, diff - pre[diff]); //to stay there 
            }
            x++;
        }
        if (und >= ov){
            cout << add + ov << endl;
            break;
        }
    }
    return 0;
}
