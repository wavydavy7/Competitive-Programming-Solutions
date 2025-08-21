#include <bits/stdc++.h>
using namespace std;

int MX = 4e5 + 10;
vector<vector<int>> tr(28, vector<int>(MX, 0));
vector<vector<int>> lz(28, vector<int>(MX, 0));
vector<vector<int>> upd(28, vector<int>(MX, 0));
 

void updaterange(int let, int idx, int l, int r, int ll, int rr, int amt){ //double means the true range we want 
    if (l > rr || r < ll) return;
    if (ll <= l && r <= rr){
        //we wanna update this, how many do we have in this range 
        tr[let][idx] = (r - l + 1) * amt; //this is being changed entirely so we don't care about overwriting the original 
        lz[let][idx] = amt;
        upd[let][idx] = 1; 
        return;
    }
    if (upd[let][idx]){
        lz[let][2*idx] = lz[let][2*idx + 1] = lz[let][idx];
        upd[let][2*idx] = upd[let][2*idx + 1] = upd[let][idx];
        if (!lz[let][idx]) {
            tr[let][2*idx] = tr[let][2*idx + 1] = 0;
        }
        else{
            tr[let][2*idx] = lz[let][idx] * (((l + r) >> 1) - l + 1);
            tr[let][2*idx + 1] = lz[let][idx] * (r - ((l + r) >> 1));
        } 
        upd[let][idx] = 0;
    } //there's a chance it wasn't even modified - in that case we don't need to propagate
    int mid = (l + r) >> 1;
    updaterange(let, 2*idx, l, mid, ll, rr, amt);
    updaterange(let, 2*idx + 1, mid + 1, r, ll, rr, amt); //why the less than 
    tr[let][idx] = tr[let][2*idx] + tr[let][2*idx + 1]; //we must update this at the end 
}

int queryrange(int let, int idx, int l, int r, int ll, int rr){
    if (l > rr || r < ll) return 0;
    if (ll <= l && r <= rr){
        return tr[let][idx];
    }
    //we're just gonna push everything down 
    if (upd[let][idx]){
        lz[let][2*idx] = lz[let][2*idx + 1] = lz[let][idx];
        upd[let][2*idx] = upd[let][2*idx + 1] = upd[let][idx];
        if (!lz[let][idx]) {
            tr[let][2*idx] = tr[let][2*idx + 1] = 0;
        }
        else{
            tr[let][2*idx] = lz[let][idx] * (((l + r) >> 1) - l + 1);
            tr[let][2*idx + 1] = lz[let][idx] * (r - ((l + r) >> 1));
        } 
        upd[let][idx] = 0;
    } //there's a chance it wasn't even modified - in that case we don't need to propagate
    int m = (l + r) >> 1;
    int lhalf = queryrange(let, 2*idx, l, m, ll, rr);
    int rhalf = queryrange(let, 2*idx + 1, m + 1, r, ll, rr);
    return lhalf + rhalf;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++){
        int val = s[i] - 'a';
        updaterange(val, 1, 0, n - 1, i, i, 1);
    }
    while (m--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        //what we gotta do is get the count for everything in this range
        int odd = 0;
        int up = 1;
        vector<int> upds(26);
        for (int i = 0; i < 26; i++){
            int val = queryrange(i, 1, 0, n - 1, l, r);
            upds[i] = val;
            if (val % 2){
                if ((r - l + 1) % 2 && !odd){
                    odd++;
                }
                else{
                    up = 0;
                    break;
                }
            }
        }
        if (!up) continue; 
        int beg = l;
        int end = r;
        for (int i = 0; i < 26; i++){
            int add = upds[i] / 2;
            updaterange(i, 1, 0, n - 1, l, r, 0);
            if (upds[i] & 1) updaterange(i, 1, 0, n - 1, (l + r) >> 1, (l + r) >> 1, 1); 
            if (!add) continue;
            updaterange(i, 1, 0, n-1, beg, beg + add - 1, 1);
            updaterange(i, 1, 0, n-1, end - add + 1, end, 1);
            beg += add;
            end -= add;
        }
    }
    string res(n, ' ');
    //now we have to get the final result
    for (int i = 0; i < n; i++){
        for (int ch = 0; ch < 26; ch++){
            if (queryrange(ch, 1, 0, n - 1, i, i) == 1){
                res[i] = 'a' + ch;
                break;
            }
        }
    }
    cout <<res;
}