#include "bits/stdc++.h"
#define pb push_back
using namespace std;

//in a tree, either the matching is up, or down...at the leaves, you might not have any matchings
//if we're talking about the leaves, then we include iff the one above it is not matched
vector<int> graph[200000];
int N;
int dp[200000][2] = {}; //initialize all to 0

//dp condition: we want the root to hold the result...
//dp[v][0] = sum(max(dp[ch_i][1], dp[ch_i][0])), dp[v][1] = 1 + dp[ch_i][0] + sum(max(dp[ch_i][1], dp[ch_i][0]))

void dfs(int node, int parent){
    
    //let's compute dp[node][0] first
    int val = 0; 
    // int leaf = 1;
    for (int i : graph[node]){
        if (i != parent){
            // leaf = 0; we don't need leaf
            dfs(i, node);
            val += max(dp[i][0], dp[i][1]); //we need to sum all of these together
        }
    }
    dp[node][0] = val;
    //we know one of them has to be 0
    // if (leaf){
    //     dp[node][0] = 0;
    //     dp[node][1] = 1;
    //     return;
    // }

    for (int i : graph[node]){
        if (i != parent){
            dp[node][1] = max(dp[node][1], dp[i][0] + val + 1 - max(dp[i][1], dp[i][0]));
        }
    }

}

int main(){
    cin >> N;
    //let's set 1 as the root 
    for (int i = 0; i < N - 1; i++){
        int one, two;
        cin >> one >> two;
        graph[one - 1].pb(two - 1);
        graph[two - 1].pb(one - 1);
    }

    dfs(0, -1);
    cout << max(dp[0][0], dp[0][1]);
}