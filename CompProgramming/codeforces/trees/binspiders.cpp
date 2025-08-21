#include <bits/stdc++.h>
//#include "debug.h"
#define pb push_back
using namespace std;


int main(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i]; 
    }
    if (k == 0) {
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                cout << " ";
            }
            cout << i + 1;
        }
        return 0;
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j){
        return a[i] < a[j];
    });
    int bit = 0; 
    while ((1 << (bit + 1)) <= k){
        bit++;
    }
    //what I can do to generalize
    vector<int> res;
    int beg = 0;
    while (beg < n){
        int end = beg; //up to which one has the same
        while (end + 1 < n && (a[ord[end + 1]] >> bit) == (a[ord[end]] >> bit)){
            end++;
        } //up comes the high bits, and if there's more than one 
        if (end + 1 < n && (a[ord[end + 1]] >> (bit + 1)) == (a[ord[end]] >> (bit + 1))){ //there should be a 1 there, and everything that has the same stuff 
            int beg2 = end + 1;
            int end2 = beg2;
            while (end2 + 1 < n && (a[ord[end2 + 1]] >> bit) == (a[ord[end2]] >> bit)){ 
                end2++;
            }
            //I need to go from beginning to end first
            
            vector<vector<int>> trie(1, vector<int>(2, -1));
            vector<int> marked(1, -1);
            for (int i = beg; i <= end; i++){
                int d = 0;
                for (int j = bit - 1; j >= 0; j--){
                    int b = (a[ord[i]] >> j) & 1;
                    if (trie[d][b] == -1){
                        trie[d][b] = trie.size();
                        trie.emplace_back(2, -1);
                        marked.pb(-1);
                    }
                    d = trie[d][b];
                }
                marked[d] = ord[i];
            }
            int found = false;
            for (int i = beg2; i <= end2; i++){
                int d = 0;
                for (int j = bit - 1; j >= 0; j--){
                    int b = ((a[ord[i]] >> j) & 1) ^ 1;
                    if (trie[d][b] == -1) b ^= 1;
                    d = trie[d][b];
                }
                //we are at the bottom 
                int comb = a[ord[i]] ^ a[marked[d]];
                if (comb >= k){
                    res.push_back(ord[i]);
                    res.push_back(marked[d]);
                    found = true;
                    break;
                }
            }
            if (!found){
                res.push_back(ord[beg]);
            }
            beg = end2 + 1;
        }
        else{
            res.push_back(ord[beg]);
            beg = end + 1;
        }
    }
    if (res.size() < 2){
        cout << -1;
        return 0;
    } 
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++){
        if (i > 0) cout << " ";
        cout << res[i] + 1;
    }
    return 0;
}