#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


int main() {
    int t; cin >> t;
    //let's do end 
    while(t--){
        int n, m, px;
        cin >> n >> m >> px;
        double p = px / 100.0;
        double q = 1.0 - p;
        int l = INT_MAX;
        int single = 0;
        debug(make_pair(p, q));
        vector<int> hs(n);
        for (int i = 0; i < n; i++){
            int h; cin >> h;
            hs[i] = h;
            l = min(l, h - 1);
        }
        for (int i = 0; i < n; i++){
            single += (hs[i] - (l + 1));
            debug(single);
        }
        //now that we have the least
        //let's define end as 
        vector<vector<vector<double>>> end(l + 2, vector<vector<double>>(n + 2, vector<double>(m + 2))); //the probability is slightly different 
        end[0][0][0] = 1; //l is the min for group shines, n is the monsters, m is the turns 
        //how do we propagate this...
        
        for (int k = 1; k <= m; k++){ //rounds
            end[0][0][k] = 1; //result of tweaking one move

            for (int i = 1; i <= l; i++){ //how many you went through 
                end[i][0][k] = p*end[i - 1][0][k - 1] + q*max(end[i][0][k - 1], end[i - 1][n - 1][k - 1]); //must have n - 1, which is resolved next line
            }
            for (int j = 1; j < n; j++){
                end[0][j][k] = p*end[0][j][k - 1] + q*end[0][j - 1][k - 1]; 
                for (int i = 1; i <= l; i++){
                    end[i][j][k] = p*end[i - 1][j][k - 1] + q*end[i][j - 1][k - 1];  //we must have j as 0 before we do anything, hence the broken for loop
                }
            } 
        }
        debug(end[1][0][2]);

        //now, we need to have something that is keeping track of the shines and singles
        vector<vector<double>> start(m + 2, vector<double>(single + 2)); //we want to see how many moves you end up at 
        start[0][0] = 1; //m is moves, l is the group shines
        for(int i = 0; i < m; i++) {
            for(int x = 0 ; x < single ; x++){
                start[i + 1][x] += start[i][x] * p;
                start[i + 1][x + 1] += start[i][x] * q;
            }
        }
        debug(start);


        //0, x or x, 0
        double ans = 0;
        for (int i = single; i <= m; i++) {
            double r = 0;
            // for (int x = 0; x <= min(i - single, l); ++x)
            //     r = max(r, end[l - x][0][m - i]);
            debug(end[l - min(l, (i - single))][0][m - i] * start[i][single]);
            ans += end[l - min(l, (i - single))][0][m - i] * start[i][single]; //how many individual ones we got rid of 
        }

        // for (int i = single; i <= m; i++){ //first time to 0 singles
        //     //how many shines there are 
        //     int shines = i - single;
        //     debug(start[i][shines] * end[shines][0][m - i]);
        //     ans += start[i][shines] * end[shines][0][m - i];
        // }   

        // vector<vector<double>> end2(single + 2, vector<double>(m + 2));

        // end2[0][0] = 1;
        // for (int rnd = 1; rnd <= m; rnd++){
        //     end2[rnd][0] = 1;
        //     for (int sing = 1; sing <= single; sing++){ //this is for singles, and the amount you have
        //         end2[rnd][sing] = p*end2[rnd - 1][sing] + q*end2[rnd - 1][sing - 1];
        //     }
        // }

        //after we get here, we need to decide what to do at each step...we can get to any combos of shines and singles... let's start from the ending config
        //double ans = 0; //I want all of the end conditions 
        // for (int j = 1; j <= l; j++){ //we need to have the change of getting there
        //     ans += start[j][0] * end[j][0][m - single - (l - j)]; //this works 
        // }
        // for (int j = 1; j <= single; j++){
        //     ans += start[0][j] * end2[m - l - (single - j)][j]; //if we have a different way of ending... 
        // }

        cout << fixed << setprecision(10) << ans << "\n";
    }
    return 0;
}
