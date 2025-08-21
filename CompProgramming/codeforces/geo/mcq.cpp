#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct pt{
    pt() = default;
    pt(ll _x, ll _y) : x(_x), y(_y) {}   
    long long x, y;
    pt operator + (const pt & p) const {
        return pt{x + p.x, y + p.y};
    }
    pt operator - (const pt & p) const {
        return pt{x - p.x, y - p.y};
    }
    long long cross(const pt & p) const {
        return x * p.y - y * p.x;
    }
};

// Monotone‐chain convex‐hull (Andrew's) → returns points in CCW order
vector<pt> convex_hull(vector<pt>& pts) {
    if (pts.size() <= 1) 
        return pts;

    // Sort by (x, then y)
    sort(pts.begin(), pts.end(), [](const pt& a, const pt& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    // Remove duplicates
    pts.erase(
        unique(
            pts.begin(), 
            pts.end(), 
            [](const pt& a, const pt& b) {
                return a.x == b.x && a.y == b.y;
            }
        ), 
        pts.end()
    );

    if (pts.size() <= 1) 
        return pts;

    vector<pt> H;
    // Build lower hull
    for (auto& p : pts) {
        while (H.size() >= 2) {
            pt a = H[H.size() - 2];
            pt b = H[H.size() - 1];
            if ((b - a).cross(p - a) <= 0) {
                H.pop_back();
            } else {
                break;
            }
        }
        H.push_back(p);
    }
    int s = H.size();
    // Build upper hull
    size_t lower_size = H.size();
    for (int i = int(pts.size()) - 2; i >= 0; i--) {
        auto& p = pts[i];
        while (H.size() > lower_size) {
            pt a = H[H.size() - 2];
            pt b = H[H.size() - 1];
            if ((b - a).cross(p - a) <= 0) {
                H.pop_back();
            } else {
                break;
            }
        }
        H.push_back(p);
    }
    // Last point is same as first, remove it
    if (H.size() > 1) 
        H.pop_back();
    return H;
}

void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < P.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<vector<pt>> gr(n);
    vector<pt> tot;
    ll res = 0;
    pt a(0, 0);
    for (int i = 0; i < n; i++){
        int g; cin >> g;
        for (int j = 0; j < g; j++){
            int x, y; cin >> x >> y;
            gr[i].emplace_back(x, y);
        }
        gr[i] = convex_hull(gr[i]); //build low then up
        a = a + gr[i][0];
        for (int j = 1; j < gr[i].size(); j++){
            tot.emplace_back(gr[i][j].x - gr[i][j - 1].x, gr[i][j].y - gr[i][j - 1].y);
        }
        int h = gr[i].size();
        tot.emplace_back(
        gr[i][0].x - gr[i][h-1].x,
        gr[i][0].y - gr[i][h-1].y
    );
        //need just the total
    }
    auto plane = [&](pt a){
        if (a.x > 0 || (a.x == 0 && a.y > 0)) return 0;
        return 1;
    };
    sort(tot.begin(), tot.end(), [&](pt a, pt b){ //sorted 
        if (plane(a) != plane(b)) return plane(a) < plane(b);
        return a.cross(b) > 0;
    });
    res = max(res, a.x*a.x + a.y*a.y);
    for (auto p : tot){
        a = a + p; 
        res = max(res, a.x*a.x + a.y*a.y);
    }
    cout << res;
    //now, I need to go one by one and merge these points together
    return 0;
}