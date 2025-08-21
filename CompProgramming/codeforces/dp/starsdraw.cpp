#include <bits/stdc++.h>
// #include "debug.h"
#define ll long long
#define pb push_back
using namespace std;
int N, M;

int main(){
    //difference arrays for easy ranges 
    cin >> N >> M;
    vector<vector<char>> grid(N, vector<char>(M)); // Use std::vector
    vector<vector<int>> left(N, vector<int>(M, 0));
    vector<vector<int>> right(N, vector<int>(M, 0));
    vector<vector<int>> up(N, vector<int>(M, 0));
    vector<vector<int>> down(N, vector<int>(M, 0));
    vector<vector<int>> s(N, vector<int>(M, 0));
    vector<vector<int>> h(N, vector<int>(M, 0));
    vector<vector<int>> w(N, vector<int>(M, 0));
    int cnt = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> grid[i][j];
        }
    }
    // debug(grid);
    for (int i = 0; i < N; i++) {
    // Initialize the first and last columns for `left` and `right`
        left[i][0] = (grid[i][0] == '*') ? 1 : 0;
        right[i][M - 1] = (grid[i][M - 1] == '*') ? 1 : 0;

        for (int j = 1; j < M; j++) {
            
            if (grid[i][j] == '*') {
                left[i][j] = 1 + left[i][j - 1];
            } else {
                left[i][j] = 0;
            }

            
            if (grid[i][M - j - 1] == '*') {
                right[i][M - j - 1] = 1 + right[i][M - j];
            } else {
                right[i][M - j - 1] = 0;
            }
        }
    }
    // debug(left);
    // debug(right);
    for (int j = 0; j < M; j++){
        //place this here first 
        up[0][j] = (grid[0][j] == '*') ? 1 : 0;
        down[N - 1][j] = (grid[N - 1][j] == '*') ? 1 : 0;
        for (int i = 1; i < N; i++){
        
            if (grid[i][j] == '*') {
                up[i][j] = 1 + up[i - 1][j];
            }
            else {
                up[i][j] = 0;
            }

            if (grid[N - i - 1][j] == '*'){
                down[N - i - 1][j] = 1 + down[N - i][j];
            }
            else {
                down[N - i - 1][j] = 0;
            }
        }
    }
    // debug(up);
    // debug(down);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            vector<int> nums = {up[i][j], down[i][j], left[i][j], right[i][j]};
            s[i][j] = *min_element(nums.begin(), nums.end()) - 1;
            if (s[i][j] > 0) cnt++;
        }
    }
    // debug(s);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            //for diff array, add to the next one on the right border 
            if (grid[i][j] == '*' && s[i][j] > 0) {
                w[i][j - s[i][j]] += 1;
                if (j + s[i][j] + 1 < M) w[i][j + s[i][j] + 1] -= 1; 
                h[i - s[i][j]][j] += 1;
                if (i + s[i][j] + 1 < N) h[i + s[i][j] + 1][j] -= 1;
            }
        }
    }
    // debug(h);
    // debug(w);
    for (int i = 0; i < N; i++){
        for (int j = 1; j < M; j++){
            w[i][j] += w[i][j - 1];
        }
    }
    for (int j = 0; j < M; j++){
        for (int i = 1; i < N; i++){
            h[i][j] += h[i - 1][j];
        }
    }
    // debug(h);
    // debug(w);
    for (int i = 0; i < N; i++){ 
        for (int j = 0; j < M; j++){
            if (!(w[i][j] > 0 || h[i][j] > 0) && grid[i][j] == '*') {
                cout << -1;
                return 0;
            }
        }
    }
    cout << cnt << endl;
    for (int i = 0; i < N; i++){ 
        for (int j = 0; j < M; j++){
            if (s[i][j] > 0) {
                printf("%d %d %d \n", i + 1, j + 1, s[i][j]);
            }
        }
    }
    return 0;
}