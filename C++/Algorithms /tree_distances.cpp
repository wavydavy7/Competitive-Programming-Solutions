//for each node, find the maximum distance to another node 
#include "bits/stdc++.h"
#define pb push_back
using namespace std;

vector<int> adj[2*100000 + 1]; //we have an array of vector<int>
//given a node, look at the kids... find the furthest one down + 1, furthest one up - 1 only if it goes through it 
//you can either go through one of the kids or the parent 
//distance through the kids is easy to find... more difficult for the parents 
//to do it for the parents, what if we do g(c1) = max(1 + g(par), 2 + f(c2)) this should be exhaustive
//can we optimize g at all? remove a factor of n?
int first[2 * 100000 + 1];
int second[2 * 100000 + 1];
int best[2 * 100000 + 1];
void dfs(int node, int par){
    for (int kid : adj[node]){
        if (kid == par) continue;
        dfs(kid, node);
        if (1 + first[kid] > first[node]){
            second[node] = first[node];
            first[node] = 1 + first[kid];
        }
        else if (1 + first[kid] > second[node]){
            second[node] = 1 + first[kid];
        }
    }
} //we take care of the sub tree dfs

void dfs2(int node, int par, int up){
    //now, we have to account for the actual best from each node
    best[node] = max(up, first[node]);
    for (auto kid : adj[node]){
        if (kid == par) continue;
        
        //if it is the best one
        if (first[node] == 1 + first[kid]){

            dfs2(kid, node, max(up, second[node]) + 1);

        }

        //if it's not the best one, we know that the best way would be to go back up 
        else { //if this kid isn't on the best downward path, we know we need to go back up

            dfs2(kid, node, best[node] + 1);

        }

    }
}
//first, we need to root it at a given node can calulate the distance to the furthest leaf 
int n;
int main(){
    cin >> n;
    for (int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        //we need to connect these two in adj
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs(1, -1); 
    dfs2(1, -1, 0);

    for (int i = 1; i < n + 1; i++){
        cout << best[i] << " ";
    }

}
//random - if you can do it in x, then all the ones are done in val1 * x. There are some additional ones requiring val2 - val1, see how many of those you need