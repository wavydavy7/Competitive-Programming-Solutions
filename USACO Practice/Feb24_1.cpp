#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

bool ok(const std::vector<std::pair<int, int>>& needs_pos, const std::vector<int>& pos, int min_y) {
    std::vector<int> max_slope;
    for (auto& [x, y] : needs_pos) {
        max_slope.push_back((y - min_y) / x); // Calculate what the max slope can be for each vertex
    }
    std::sort(max_slope.begin(), max_slope.end());

    return std::is_sorted(pos.begin(), pos.end()) && std::equal(pos.begin(), pos.end(), max_slope.begin(), std::less_equal<>());
}

int solve_min(std::vector<std::pair<int, int>>& needs_pos, std::vector<int>& pos) {
    std::sort(pos.begin(), pos.end());

    int min_y = INT_MAX;
    for (auto& [x, y] : needs_pos) {
        min_y = std::min(min_y, y);
    }

    int hi = min_y;
    int lo = min_y - pos.back() * std::max_element(needs_pos.begin(), needs_pos.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    })->first;

    assert(ok(needs_pos, pos, lo));

    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (ok(needs_pos, pos, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int solve_max(std::vector<std::pair<int, int>>& needs_neg, std::vector<int>& neg) {
    std::vector<std::pair<int, int>> needs_pos;
    std::vector<int> pos;
    for (auto& [x, y] : needs_neg) {
        needs_pos.push_back({x, -y});
        pos.push_back(-y);
    }
    return -solve_min(needs_pos, pos);
}

int main() {
    int T, N, x1;
    std::cin >> T;
    while (T--) {
        std::cin >> N >> x1;
        std::vector<std::pair<int, int>> needs_pos, needs_neg;
        std::vector<int> pos, neg, with_x1;
        for (int i = 0; i < N; ++i) {
            int y1, y2, x2;
            std::cin >> y1 >> y2 >> x2;
            with_x1.push_back(y1);
            with_x1.push_back(y2);
            needs_pos.push_back({x2, y1});
            needs_neg.push_back({x2, y2});
        }

        for (int i = 0; i < 4*N; ++i) {
            int slope;
            std::cin >> slope;
            if (slope < 0) {
                neg.push_back(slope);
            } else {
                pos.push_back(slope);
            }
        }

        if (neg.size() < N || pos.size() < N) {
            std::cout << "-1\n";
            continue;
        }

        std::sort(with_x1.begin(), with_x1.end());
        for (int y : with_x1) {
            if (needs_neg.size() < neg.size()) {
                needs_neg.push_back({x1, y});
            } else {
                needs_pos.push_back({x1, y});
            }
        }

        int y_min = solve_min(needs_pos, pos);
        int y_max = solve_max(needs_neg, neg);
        std::cout << y_max - y_min << '\n';
    }
    return 0;
}



// #include <iterator>
// #include <iostream>
// #include <vector>
// #include <set>
// #include <unordered_map>
// #include <array>
// #include <cmath>
// #include <algorithm>
// #include <numeric> 
// using namespace std;
// typedef long long ll;
// int N;
// int targets;
// int leftmost;


// boolean findY(vector<pair<ll,ll>> &rpts, vector<ll> &rslopes, int y){ //I set a y value, and for each value, I find the maximum minimum I can use to stay at or above y 
//     sort(rslopes.rbegin(), rslopes.rend());
//     for (auto &element : rpts){

//     }
// }
// int solve(vector<pair<ll,ll>> &free, vector<pair<ll,ll>> &lcorners, vector<pair<ll,ll>> &ucorners, vector<ll> &s){
    
//     //out of the slopes
//     ll positives = accumulate(s.begin(), s.end(), 0, [](ll sum, ll element){
//         return sum + (element > 0 ? 1 : 0);
//     });
//     if (positives < N || positives > 3*N){
//         return -1;
//     }
//     sort(free.rbegin(), free.rend()); //I have from top down 
//     ll diff = positives - N;
//     for (auto &elem : free){
//         if (diff > 0){
//             lcorners.push_back(elem); //we want the positive slopes to belong to the lcorners
//             diff--;
//         }
//         else{
//             ucorners.push_back(elem);
//         }
//     }
//     sort(free.begin(), free.end());
//     ll min_y = free.front().second;
//     sort(lcorners.rbegin(), lcorners.rend());
//     ll max_x = lcorners.front().first;
//     ll lo = min_y - s.front() *  max_x;
//     ll hi = min_y;
//     sort(s.rbegin(), s.rend()); //reversed
//     vector<int> pos_slopes(s.begin(), s.begin() + (positives - N));
//     while (lo < hi){
//         ll mid = (lo + hi) / 2;
//         bool res = findY(lcorners, s, pos_slopes);
//         if (res){
//             lo = mid;
//         }
//         else{
//             hi = mid - 1;
//         }
//     }
//     return lo;
// }

// int main(){
//     cin >> N;
//     for (int i = 0; i < N; i++){
//         cin >> targets;
//         cin >> leftmost;
//         ll x2;
//         ll y1;
//         ll y2;
//         vector<pair<ll, ll>> free;
//         vector<pair<ll, ll>> lcorners;
//         vector<pair<ll, ll>> ucorners;
//         for (int j = 0; j < targets; j++){
//             cin >> y1;
//             cin >> y2;
//             cin >> x2;
//             free.push_back({leftmost, y1});
//             free.push_back({leftmost, y2});
//             lcorners.push_back({x2, y1});
//             ucorners.push_back({x2, y2});
//         }
//         vector<ll> slopes;
//         for (int k; k < 4*targets; k++){
//             ll add;
//             cin >> add; 
//             slopes.push_back(add);
//         }

//         solve(free, lcorners, ucorners, slopes);
//     }
// }