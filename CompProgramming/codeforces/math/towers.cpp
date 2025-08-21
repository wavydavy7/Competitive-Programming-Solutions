#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &as, int m, int n){
    vector<int> AddTo(n, 0);
    int sub = 0;
    for (int i = 0; i < n; i++){
        sub += AddTo[i]; 
        int desired = max(0, i - (n - m + 1) + 1); //this is the amount the reaches here, but there must be some values that hit it before removed
        int reached = i - sub; //the amount k_i that can reach here, but desired amounts come after so they're not included when it's destroyed to 0
        if (reached < desired) return 0;
        int jump = i + as[i] + ((i - sub) - desired) + 1;
        if (jump < n) AddTo[jump]++; //first part is the reach, but you have to subtract desired because desired amounts are 
    }
    return 1;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> as(n);
        for (int i = 0; i < n; i++){
            cin >> as[i];
        }
        //we need to figure out if it's possible 
        int l = 0;
        int r = n + 1;
        while (r - l > 1){
            int m = (l + r) >> 1;
            if (solve(as, m, n)){
                l = m;
            }
            else{
                r = m;
            }
        }
        cout << l << endl;
    }
}