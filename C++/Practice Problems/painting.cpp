#include <bits/stdc++.h>
 
using namespace std;
 
#define forn(i, n) for (int i = 0; i < int(n); i++)
//you want to cover from left to right... and you want to know the direction
int main() {
    int t;
    cin >> t;
    forn(tt, t) {
        int n;
        cin >> n;
        vector<int> a(n);
        forn(i, n)
            cin >> a[i];
 
        vector<vector<vector<int>>> d(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INT_MAX)));
        d[0][0][0] = 0;
 
        forn(i, n) 
            forn(j, n) //j is the furthest distance to an unpainted cell
                forn(k, n + 1) 
                    if (d[i][j][k] < INT_MAX) { //you start at int max
                        int ai = a[i]; //what distance you can achieve here 
 
                        // Z
                        {
                            int ni = i + 1; //you can only start somewhere that's already been covered
                            int nj = j > 0 ? j + 1 : (k == 0 ? 1 : 0);
                            int nk = max(0, k - 1);
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k]); //going here from L, if nj = 0 and k != 0, then nj can = 0
                        }
 
                        // L
                        {
                            int ni = i + 1;
                            int nj = j > 0 ? j + 1 : 0;
                            if (nj <= ai) //substracting one, which is how many it can cover... if the ai is more...that's something you can use 
                                nj = 0; //why do you make nj = 0 here? you want it to surpass the current left boundary...so the 0 doesn't stand for anything
                            int nk = max(0, k - 1); 
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k] + 1); //you go from left to right, only if the left side allows 
                        }
 
                        // R
                        {
                            int ni = i + 1;
                            int nj = j > 0 ? j + 1 : 0;
                            int nk = max(ai - 1, k - 1);
                            d[ni][nj][nk] = min(d[ni][nj][nk], d[i][j][k] + 1); //why can't you just go on and on from a certain location?
                        }
                    }
 
        cout << *min_element(d[n][0].begin(), d[n][0].end()) << endl; //literally the very end 
    }
}
