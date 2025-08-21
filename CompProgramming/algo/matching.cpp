#include <bits/stdc++.h>
using namespace std;

// Function to perform Gale-Shapley algorithm
vector<int> galeShapley(vector<vector<int>> guys, vector<vector<int>> girls, int n) {
    // Create a vector to store the current match for each woman (-1 means unmatched)
    vector<int> matchings(n, -1);
    
    // Create a vector to store the next proposal index for each man
    vector<int> next_proposal(n, 0);
    
    // Create a map to store each woman's preference rank for each man
    // Using vector<vector<int>> for constant-time lookups
    vector<vector<int>> women_rank(n, vector<int>(n, 0));
    for (int w = 0; w < n; w++) {
        for (int rank = 0; rank < n; rank++) {
            int m = girls[w][rank];
            women_rank[w][m] = rank;
        }
    }
    
    // Initialize a queue with all free men
    queue<int> free_men;
    for (int m = 0; m < n; m++) {
        free_men.push(m);
    }
    
    // Perform the Gale-Shapley algorithm
    while (!free_men.empty()) {
        int m = free_men.front();
        free_men.pop();
        
        // Get the next woman to propose to
        if (next_proposal[m] >= n) {
            continue; // This man has proposed to all women
        }
        
        int w = guys[m][next_proposal[m]];
        next_proposal[m]++;
        
        if (matchings[w] == -1) {
            // Woman is free, match her with this man
            matchings[w] = m;
        } else {
            int current_m = matchings[w];
            // Check if the new man is preferred over the current match
            if (women_rank[w][m] < women_rank[w][current_m]) {
                // Woman prefers the new man, so match her with the new man
                matchings[w] = m;
                // The previous man becomes free again
                free_men.push(current_m);
            } else {
                // Woman prefers her current match, so the new man remains free
                free_men.push(m);
            }
        }
    }
    
    return matchings; // matchings[w] = m means woman w is matched to man m
}

int main(){
    // Example usage:
    int n = 4;
    
    // Men's preferences (guys)
    // Each man ranks women from most preferred (left) to least preferred (right)
    vector<vector<int>> guys = {
        {0, 1, 2, 3}, // Man 0 prefers Woman 0 the most, then 1, 2, 3
        {1, 0, 3, 2}, // Man 1 prefers Woman 1, then 0, 3, 2
        {0, 1, 2, 3}, // Man 2 prefers Woman 0, then 1, 2, 3
        {1, 2, 3, 0}  // Man 3 prefers Woman 1, then 2, 3, 0
    };
    
    // Women's preferences (girls)
    // Each woman ranks men from most preferred (left) to least preferred (right)
    vector<vector<int>> girls = {
        {0, 1, 2, 3}, // Woman 0 prefers Man 0 the most, then 1, 2, 3
        {1, 0, 3, 2}, // Woman 1 prefers Man 1, then 0, 3, 2
        {2, 3, 1, 0}, // Woman 2 prefers Man 2, then 3, 1, 0
        {3, 2, 1, 0}  // Woman 3 prefers Man 3, then 2, 1, 0
    };
    
    vector<int> matchings = galeShapley(guys, girls, n);
    
    // Output the matchings
    for(int w = 0; w < n; w++) {
        cout << "Woman " << w << " is matched to Man " << matchings[w] << endl;
    }
    
    return 0;
}
