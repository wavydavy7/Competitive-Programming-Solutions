#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    int n1; cin >> n1;
    vector<ll> d1(n1);
    set<ll> relev;
    for (int i = 0; i < n1; i++){
        cin >> d1[i];
        relev.insert(d1[i]);
        relev.insert(max(1LL, d1[i] - 1));
        relev.insert(d1[i] + 1);
        
    }
    int n2; cin >> n2;
    vector<ll> d2(n2);
    for (int i = 0; i < n2; i++){
        cin >> d2[i];
        relev.insert(d2[i]);
        relev.insert(max(1LL, d2[i] - 1));
        relev.insert(d2[i] + 1);
    }
    sort(d1.begin(), d1.end());
    sort(d2.begin(), d2.end());
    // I need to go through all the points
    //which one's the winning dice?
    float win1 = 0;
    auto prob = [&](int x, vector<ll>& dice){
        double res = 0;
        auto it = upper_bound(dice.begin(), dice.end(), x); //how many are <= 
        res += (it - dice.begin());  
        res += (lower_bound(dice.begin(), dice.end(), x) - dice.begin()); //we also get those that are < 
        return res / 2 / dice.size();
    };
    for (auto x : d1){
        win1 += prob(x, d2);
    }
    win1 /= d1.size();
    debug(win1);
    if (win1 < 0.5) {
        swap(d1, d2);
        swap(n1, n2);
    }
    //now we need to make a convex hull
    vector<pair<double, double>> pts;
    for (auto pt : relev){
        float ag2 = prob(pt, d2);
        float ag1 = prob(pt, d1);
        pts.push_back({ag1, ag2});
    }

    vector<ll> hull;
    for (int i = 0; i < pts.size(); i++){
        while (hull.size() >= 2){
            auto [x1, y1] = pts[hull[hull.size() - 2]];
            auto [x2, y2] = pts[hull[hull.size() - 1]];
            auto [x3, y3] = pts[i];
            if ((x3 - x1) * (y2 - y1) < (x2 - x1) * (y3 - y1)) break;
            hull.pop_back();
        }
        hull.push_back(i);
    }
    //vertical line first
    double ans = 0;
    for (int i = 0; i < hull.size() - 1; i++){
        //we need to look at the next one
        auto [x1, y1] = pts[hull[i]];
        auto [x2, y2] = pts[hull[i+1]];
        if (x1 <= 0.5 && x2 >= 0.5){
            double slope = (y2 - y1) / (x2 - x1);
            double val = slope * (0.5 - x1) + y1;
            ans = val;
        }
    }
    cout << fixed << setprecision(9) << ans << " ";
    for (auto& pt : pts){
        swap(pt.first, pt.second);
        pt.first = 1 - pt.first;
        pt.second = 1 - pt.second;
    }
    hull.clear();
    reverse(pts.begin(), pts.end());

    for (int i = 0; i < pts.size(); i++){
        while (hull.size() >= 2){
            auto [x1, y1] = pts[hull[hull.size() - 2]];
            auto [x2, y2] = pts[hull[hull.size() - 1]];
            auto [x3, y3] = pts[i];
            if ((x3 - x1) * (y2 - y1) < (x2 - x1) * (y3 - y1)) break;
            hull.pop_back();
        }
        hull.push_back(i);
    }
    //vertical line first
    ans = 0;
    for (int i = 0; i < hull.size() - 1; i++){
        //we need to look at the next one
        auto [x1, y1] = pts[hull[i]];
        auto [x2, y2] = pts[hull[i+1]];
        if (x1 <= 0.5 && x2 >= 0.5){
            double slope = (y2 - y1) / (x2 - x1);
            double val = slope * (0.5 - x1) + y1;
            ans = val;
        }
    }
    cout << fixed << setprecision(9) << 1 - ans;
    
    return 0;
}
