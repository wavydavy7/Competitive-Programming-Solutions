#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 998244353;
constexpr int MAXC = 1e6 + 2;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >>k;
    vector<int> cs(n);
    for (int i = 0; i < n; i++){
        cin >> cs[i];
    }

    
    //I want to find the prime factorization of all elements
    vector<int>primes(MAXC, 0);
    //set<int> ps;
    for (int i = 2; i < MAXC; i++){
        if (primes[i] == 0){
            //ps.insert(i);
            for (int j = i; j < MAXC; j += i){
                primes[j] = i; //the primes should have themselves in the primes vector
            }
        }
    }
    vector<int> cmp(MAXC, 0);
    vector<int> kmp(MAXC, 0);
    auto factors = [&](int x, int boo){
        while (x > 1){
            int p = primes[x];
            int cnt = 0;
            while (x % p == 0){
                x /= p;
                cnt++;
            }
            if (boo){
                cmp[p] = max(cmp[p], cnt);
            }
            else{
                kmp[p] = cnt;
            }
        
        }
    };
    factors(k, 0);
    for (int c : cs){
        factors(c, 1);
    } //we do this 
    for (int prime = 2; prime < MAXC; prime++){
        if (kmp[prime] > cmp[prime]){
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}