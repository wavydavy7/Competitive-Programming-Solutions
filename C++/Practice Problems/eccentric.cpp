//this is a stupid problem :(( spent like 16 hours on this
#define push_back pb

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <numeric>
using namespace std;


int main(){
    int N, K;
    cin >> N >> K;
    map<int, vector<int>> tree;
    for (int i = 0; i < N; i++) {
        tree[i] = vector<int>(N, 0);
    }
    map<int, vector<int>> inv_tree;
    for (int i = 0; i < N; i++) {
        inv_tree[i] = vector<int>(N, 1);
    }
    map<int, int> deg;
    for (int i = 0; i < N - 1; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        tree[a][b] = 1;
        tree[b][a] = 1;
        inv_tree[a][b] = 0;
        inv_tree[b][a] = 0;
        deg[a]++;
        deg[b]++;
    }
    
    int orig = 0;
    vector<int> endpts(N, 0);
    for (auto &it : deg){
        if (it.second > 2){
            orig += (it.second - 2); 
        } 
        else if (it.second == 1){ //what it maps to
            endpts[it.first] = 1; 
        }
    }
    
    vector<int> inv_nodes(N, 1);
    
    for (auto &it: inv_tree){
        if (accumulate(it.second.begin(), it.second.end(), 0) == 0){
            inv_nodes[it.first] = 0; //remove from inverse nodes 
        }
    }
    if (orig > K || K > accumulate(inv_nodes.begin(), inv_nodes.end(), 0) - 1){ //you need more jumps 
        cout << -1;
        return 0;
    }
    
    //will need to place on points
    vector<int> res;
    vector<int> placed(N, 0);
    
    //you should only use heaps if you want to access the first and last elements
    
    //what are some conditions for placing 
    int amt = N + 1; 
    int cur
     = -1;
    //orig represents how many jumps you need 

    int final;
    //how many nodes can actually be reached in the graph
    function <vector<int>(int, int)> rec = [&](int many, int on) -> vector<int>{ //I need to put a flag on this one

        if (many == final){
            // cout << "yay";
            return vector<int>{on + 1};
        }
        // else if (accumulate(inv_tree[on].begin(), inv_tree[on].end(), 0) == 0){
        //     //find a diff one 
        //     cout << "shift from " << on; 
        //     for(int i = 0; i < N; i++){
        //         if (accumulate(inv_tree[i].begin(), inv_tree[i].end(), 0) > 0){ //try to jump to one 
        //             cout << "to " << i;
        //             inv_nodes[i] = 0;
        //             return rec(many, i);
        //         }
        //     }
        // }
        //use for loop to go through all of the available ones, try the lowest, then the second lowest, blah blah... you should start with smth that works
        for(int i = 0; i < N; i++){
            
            if (i != on && inv_nodes[i] && inv_tree[i][on]){ //inv_nodes should have a 1
                cout << "adding " << i;
                inv_nodes[i] = 0;
                vector<int> test = rec(many + 1, i);
                test.pb(on + 1);
                inv_nodes[i] = 1;
                if (!test.empty() && test[0] != -1){
                    return test;
                }
            }
        }
        return vector<int>{-1};
    };

    for (int i = 0; i < N; i++){
        inv_tree[i][i] = 0;
    }

    auto cnt = [&] (int node)
    {
        int res = 0;
        for (int i = 0; i < N; i++){
            if (!placed[i] && tree[node][i]) res++;
        }
        return res;
    };

    auto rem = [&] (int cur
    ){
        int res = 0;
        for (int i = 0; i < N; i++){ //check whether anything connected to it
            if (inv_nodes[i] != 0 && accumulate(inv_tree[i].begin(), inv_tree[i].end(), 0) > 0){
                res++;
            }
        }
        return res - 1;
    };
    // int num = 1;
    
    while (amt--){
        // cout << "num " << num << cur
        cout << "\n";
        // num++;
        //everytime you jump, you actually increase your required jumps by 1 and decrease allowed jumps by 1(2 diff)
        int next;
        int saved;
        //if you go to your neighbor, you save a jump 
        final = rem(cur);
        cout << "current " << cur + 1 << "\n";
        cout << "final " << final << "\n";
        // cout << jump_size << "\n";

        if (orig == K){ //if (orig == K , honestly else right here //you kinda need to move side to side 
            cout << "too many \n" << cur
            ;
            bool flag = false;
            
            for (int i = 0; i < N; i++){
                
                if (cur
                 == -1 || (!placed[i] && cur != i)){ 
                    
                    if ((cur
                     == -1 && endpts[i]) || (cur != -1 && i != cur
                     && tree[cur
                    ][i] != 0)){ //try to go to neighbor
                        flag = true;
                        saved = i;
                        cout << "nei nei" << saved;
                        break;
                    }
                    
                }
            }
            
            
            if (!flag){
                for (int i = 0; i < N; i++){
                    if (!placed[i] && endpts[i] && i != cur
                    ){
                        saved = i;
                        cout << "jump";
                        break;
                    }
                }
            }
            
        }
        else if (K == (final - 1)){ 
            cout << "ending";
            bool flag = false;
            // for (int i = 0 ; i < N; i++){
            //     if (!placed[i] && accumulate(inv_tree[i].begin(), inv_tree[i].end(), 0) == 0){
            //         saved = i;
            //         cout << saved;
            //         flag = true;
            //         break;
            //     }
            // }
            if (! flag){
                cout << "too few \n";
                cout << "rec" << cur
                 << final;
                cout << inv_tree[0][2];
            //if there's more things to connect to just do it
                vector<int> last = rec(0, cur
                );
                reverse(last.begin(), last.end());
                res.insert(res.end(), last.begin(), last.end());
                //you're going to use recursion to find the available configs from inv_tree, add in anything that wasn't in the inv_tree
                break;
            }
            
        }
        
        else { // if (orig < K) you can keep going
            cout << "going " << cur
             << "\n";
            
            for (int i = 0; i < N; i++){
                if (!placed[i] && cur
                 != i){ 
                    
                    if (cur== -1 || tree[cur][i] == 0){ 
                        if (cur == -1 || cnt(cur) == 0){ //you're literally at the end 
                            // orig--;
                            // K--;
                            //doesn't actually change 
                            saved = i;
                            // cout << saved;
                            break;
                        }
                        //is not a neighbor
                        //if no more edges to visit 
                        else if (orig + 1 <= K - 1){
                            orig++;
                            K--;
                            //I also need to label these points as jumpable ones
                            for (int nei = 0; nei < N; nei++){
                                if (tree[i][nei] == 1){
                                    endpts[nei] = 1;
                                }
                            }
                            cout << "ki" << K << i;
                            saved = i;
                            // cout << saved;
                            break;
                        }
                    }
                    saved = i;
                    // cout << saved;
                    break;
                    
                }
                
                

            }
        }
        
            
        if (cur!= - 1){
            res.pb(cur+ 1); 
            cout << "put this "<< cur
             + 1 << " \n";
            // cout << "enter " << cur
             + 1;
            placed[cur] = 1;
            inv_nodes[cur] = 0;
            for (int i = 0; i < N; i++){
                inv_tree[i][cur] = 0;
                inv_tree[cur][i] = 0;
            }
        }
        cur = saved;
            //within the inverse 
        }
        // cout << res[num - 2] << "\n";

        
        //if it's equal to k, you must try endgame tactic
        
        //risks:
        //1)if you greedily get your neighbors, you'll have too many extra jumps in the end
        //Never let your nodes fall below max jumps(once you hit this, start jumping every time)
        //there are several configs that let you achieve max jumps... how many of these configs are there)? You want to connect all points with
        //don't slide to smth that gives you no jumps... use backtracking 
        
        //2)if you jump too much, you won't have enough
        //keep a record of how many things you're required to do(before you hit the limit, jump to your limit to the lowest end point node and greedily eat smth up until you no longer can)
        //for the endpts, you just can't jump to one with > 1 edges not counting the one connected to a double circle 
    for (int i = 1; i < N + 1; i++){
        if (find(res.begin(), res.end(), i) == res.end()) res.pb(i);
    }
    
    for (int elem : res){
        cout << elem << " ";
    }
    return 0;
}

//ways of increasing orig - jumping to the middle
//ways of decreasing orig - 