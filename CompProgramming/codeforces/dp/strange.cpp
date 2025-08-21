#include <bits/stdc++.h>
//#include "debug.h"
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<array<int, 3>> vals;
    int br = -1;
    int ans = 0;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        for (auto& v : vals){
            v[2] = gcd(v[2], x); //we can modify this now 
        }
        vals.push_back({i, i, x}); //prefix
        int s = vals.size();
        
        int cont = 0;
        for (int j = 0; j < s; j++){
            if (cont > 0 && vals[cont - 1][2] == vals[j][2]){
                vals[cont - 1][1] = vals[j][1];
            }
            else{
                vals[cont++] = vals[j];
            }
        }
        vals.resize(cont);

        for (auto& v : vals){
            int wh = i - v[2] + 1;
            if (v[0] <= wh && wh <= v[1]){
                if (wh > br){
                    br = i;
                    ans++;
                }
            }
        }
        cout << ans << " ";
    }
    return 0;
}
