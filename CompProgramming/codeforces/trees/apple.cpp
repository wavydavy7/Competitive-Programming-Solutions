#include <bits/stdc++.h>
using namespace std;

vector<int64_t> fact;
int64_t C(int n, int k) {
  if (k == 2){
    return 1LL * n * (n - 1)/2;
  }
  if (k == 3){
    return 1LL * n * (n - 1) * (n - 2) / 6;
  }
  return 0;
}

int main(){
    int t;
    cin >> t;
    fact.push_back(1);
    while (t--){
        int64_t n, k;
        cin >> n >> k; //I have n, I want to get to k
        if (C(n, 3) + 1 < k) {
            cout << "No" << endl;
            continue;
        }
        //now I need to build the tree
        int64_t diff = C(n, 3) - min(k, C(n, 3)); 
        int64_t on = n - 1; //on = gap
        cout << "Yes" << endl;
        for (int i = n; i >= 2; i--){ //which node you're on... you can only move the second one
            while (on * (on - 1) / 2 > diff){
                on--;
            }
            diff -= on * (on - 1) / 2;
            cout << i <<  " " << (i - on) << endl;
            if (on != 1) on--; //shorten the gap
        }
    }
}