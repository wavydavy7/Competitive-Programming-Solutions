#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return x;
}
double ternary_search(double l, double r) { //for pyramid, change conditions for valleys
    double eps = 1e-9;              
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      
        double f2 = f(m2);      
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                
}

int binary(int k, int n){
    vector<int> a(n);
    int l = -1, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (k < a[m]) {
            r = m; // a[l] <= k < a[m] <= a[r]
        } else {
            l = m; // a[l] <= a[m] <= k < a[r]
        }
    }//l holds last element less(or satisfying some other constraint), r holds first element greater
}


