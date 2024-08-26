#include <bits/stdc++.h>
using namespace std;
int N; 
double dist[20][20], memo[1 << 16], x[20], y[20];



int main(){
    auto distance = [&](pair<int, int> a, pair<int, int> b){
        return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
    };
    
    //what can the dp states be? We could store a binary number to indicate that this one is taken
    //we want dp[111...], so for each value, choose one to include or exclude 
    //int extends till 2 x 10^9
    function<double(int)> matching = [&](int bitmask) -> double{
        //find the most significant bit 
        if (memo[bitmask] > -0.5){
            return memo[bitmask];
        }
        if (bitmask == (1 << (2*N)) - 1){
            return memo[bitmask] = 0;
        }

        double ans = 200000000000.0;
        for (int i = 0; i < 2*N; i++){
            if (!(bitmask & (1 << i))){
                for (int j = i + 1; j < 2*N; j++){
                    if (!(bitmask & (1 << j))){
                        ans = min(ans, dist[i][j] + matching(bitmask | (1 << i) | (1 << j)));
                    }
                }
                break;
            }
        }
        return memo[bitmask] = ans;
    };

    int caseNum = 1;
    string names[100];
    while (cin >> N){
        if (N == 0){
            break;
        }
        for (int val = 0; val < 2*N; val++){
            cin >> names[val] >> x[val] >> y[val];
        }
        for (int i = 0; i < 2*N; i++){
            for (int j = 0; j < 2*N; j++){
                dist[i][j] = distance({x[i], y[i]}, {x[j], y[j]});
            }
        }
        memset(memo, -1, sizeof memo);
        cout << "Case " << caseNum++ << ": " << fixed << setprecision(2) << matching(0) << endl;
    }
}