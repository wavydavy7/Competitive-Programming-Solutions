#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main() { 
  int N, W; 
  while (cin >> N >> W) {
    vector<string> D(N);
    for (auto& d : D) cin >> d; //for each of the dice

    map<string, vector<int>> dw; 
    function<void(int,int,string)> doit = [&](int d, int b, string s) {
      if (d == N) {
        sort(s.begin(), s.end());
        dw[s].push_back(b); //you map every string to a vector of positions 
        return;
      }
      for (int i = 0; i < D[d].size(); i++) doit(d+1, b + ((i+1)<<(3*d)), s+D[d][i]); //add the ith character, move on to the next dice, with some sort of encoding b
      //i_th dice 1-based, plus which of the dice(we know there a maximum of 6 dice)...this generates all permutations
    };
    doit(0, 0, ""); //so you can make some states, and you hash the value you want to those relevant states
    // for (auto i = dw.begin(); i != dw.end(); i++) {
    //     for (auto j = i->second.begin(); j != i->second.end(); j++){
    //         cout << i->first << "\t "<< *j << endl; 
    //     }
    // }
    vector<int> curn(1<<(3*N)), seen(1<<(3*N));
    vector<double> cure(1<<(3*N)), beste(1<<(3*N), 1e9);
    priority_queue<pair<double, int>> q; //apparently this is a max queue... dope
    // For a solved full configuration, adjust the expected values of partial configurations that may roll it. I think this is the bottom up solution
    function<void(int,int,int,double)> sete = [&](int d, int pw, int b, double e) {
      if (d == N) {
        if (pw == 1) return; //these are the results desired
        curn[b]++; //the b gets one more, how many words it's connected to
        cure[b] += e; //e stays the same the whole time...first time through nothing changes
        // We know that be = 1 + ((pw-curn) / pw) * be + (curn / pw) * (cure/curn).
        double be = (pw + cure[b]) / curn[b]; //the p  = curn[b] / (pw + cure[b])..pretty much calculates the value right now as going from 1 to any of them 
        beste[b] = be;
        q.push({-be, b}); //you push in val for the star nodes 
        return;
      }
      sete(d+1, pw, b, e); //when you reroll, you reroll all the ones you don't want
      sete(d+1, pw*D[d].size(), b & ~(7<<(3*d)), e); //pretty much adjusting the transition states...you could reroll... or you don't have to(this takes a few steps back)
    };

    // For a solved partial configuration, any unsolved full configurations that can reach it are now solved.
    function<void(int,int,double)> brec = [&](int d, int b, double e) {
      if (d == N) {
        if (!seen[b]) sete(0, 1, b, e); //if it hasn't been seen, sete this for a given word 
        seen[b] = true; //first, for all the ending states
        return;
      }
      if (b&(7<<(3*d))) { //if there is some letter here 
        brec(d+1, b, e); //go to the next dice, don't remove anything
      } else {
        for (int i = 0; i < D[d].size(); i++) brec(d+1, b + ((i+1)<<(3*d)), e); //if you don't use the one on that dice, go through all the options and add it in 
      }
    };
    //what is the expected value directly there! then your words know, so they greedily go to the smaller ones, and then we know the missing letter ones connect to the fully missing letter ones 
    for (int i = 0; i < W; i++) {
      string w;
      cin >> w; //I wanna go through every word, sort it
      sort(w.begin(), w.end()); //sort the letters in word, go to the word, and b rec it 
      for (auto b : dw[w]) brec(0, b, 0.0); //start with one of the configs matched by the dice rolled
    }


    if (q.empty()) { cout << "impossible" << endl; continue; }
    while (!q.empty()) { 
      auto [e, b] = q.top(); q.pop(); e = -e;
      if (seen[b]) continue;
      seen[b] = true;
//for (int d = 0; d < N; d++) if (b&(7<<(3*d))) cout << D[d][((b>>(3*d))&7)-1]; else cout << '.';
//cout << ": " << e << endl;
      // Configuration b is now solved.
      brec(0, b, e); //e is the expected value
    }

    cout << fixed << setprecision(9) << beste[0] << endl; //from the start 
  }
}

//you have to start at the ends and get a probability of going from each state. Next, you want to connect all the states to the actual words. When you connect to an actual word,
//use your existing probabilities to greedily go to the next one in case it fails