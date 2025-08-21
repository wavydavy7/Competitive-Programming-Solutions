#include <bits/stdc++.h>
using namespace std;

double lcs(vector<int>& a, double sub){
    double gpos = 0;
    double gneg = 0;
    double pos = 0; 
    double neg = 0;
    for (auto x : a){
        double modified = x - sub;
        pos = max(pos + modified, modified);
        gpos = max(gpos, pos);
        neg = min(neg + modified, modified);
        gneg = min(gneg, neg);
    }
    return max(gpos, -gneg);
};

const double epsilon = 1e-11;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    //determine weakness 
    double l = *min_element(a.begin(), a.end());
    double r = *max_element(a.begin(), a.end());
    while (r - l > epsilon){
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = lcs(a, m1);
        double f2 = lcs(a, m2);
        if (f1 < f2)
            r = m2;
        else
            l = m1;
    }
    double x  = 0.5 * (l + r);          // point closest to the real minimum
    double ans = lcs(a, x);               // evaluate there
    cout << fixed << setprecision(12)       // a couple extra digits never hurt
         << ans << '\n';
}