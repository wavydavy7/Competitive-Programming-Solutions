// // // O(n log k + sqrt(k) * log(k) + d(k)^2 * p(k)) solution, model solution for the harder version

// #include <algorithm>
// #include <iostream>
// #include <map>
// #include <set>
// #include <vector>
// typedef long long ll;
// using namespace std;

// // int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
// // void upd(int& a, int b) { a = max(a, b); }

// // void prepare(int x, vector<int>& dx, vector<int>& px, vector<int>& cx, map<int, int>& mx)
// // {
// //     vector<int> cntx;
// //     for (int i = 2; i * i <= x; i++) if (x % i == 0) 
// //     {
// //         px.push_back(i), cntx.push_back(0);
// //         while (x % i == 0) cntx.back()++, x /= i; //how many times i goes into x?
// //     }
// //     if (x > 1) px.push_back(x), cntx.push_back(1);
// //     dx.push_back(1);
// //     for (int i = 0; i < px.size(); i++)
// //     {
// //         cx.push_back(dx.size()); //your cx actually gets the size of the values before adding all the possibilities for a given prime factor
// //         for (int j = 0; j < cx.back() * cntx[i]; j++) dx.push_back(dx[j] * px[i]); //px[i] is pretty important, you're multiplying that by dx[j]
// //     }
// //     for (int i = 0; i < dx.size(); i++) mx[dx[i]] = i; //maps an element to the index in dx
// // }
// // vector<ll> solve(int n, vector<int> a, vector<int> b, vector<ll> c, vector<ll > qu)
// // {
// //     int k = max(*max_element(a.begin(), a.end()), *max_element(b.begin(), b.end())) + 1; //I'm going to get the max element out of everything 
// //     vector<int> g(n);
// //     for (int i = 0; i < n; i++) g[i] = gcd(a[i], b[i]); //Get the gcd of the pair of numbers
// //     vector<pair<ll, int> > v;
// //     vector<ll> ans;
// //     for (int it = 0; it < 2; it++) //just do it two times, fixed and swapped
// //     {
// //         vector<int> da, pa, ca, db, pb, cb;
// //         map<int, int> ma, mb;
// //         prepare(a[0], da, pa, ca, ma), prepare(b[0], db, pb, cb, mb);
// //         vector<vector<ll> > p(da.size(), vector<ll>(db.size(), 0)); //Some 2D arrays 
// //         vector<vector<ll> > d(da.size(), vector<ll>(db.size(), 0));
// //         for (int i = 1; i < n; i++) //for the number of elements in a and b
// //         {
// //             p[ma[gcd(a[0], a[i])]][mb[gcd(b[0], b[i])]] += 1, d[ma[gcd(a[0], a[i])]][mb[gcd(b[0], b[i])]] += 0;
// //             p[ma[gcd(a[0], b[i])]][mb[gcd(b[0], a[i])]] += 1, d[ma[gcd(a[0], b[i])]][mb[gcd(b[0], a[i])]] += c[i];
// //             p[ma[gcd(a[0], g[i])]][mb[gcd(b[0], g[i])]] -= 1, d[ma[gcd(a[0], g[i])]][mb[gcd(b[0], g[i])]] -= c[i];
// //         }
// //         //ca is the counts of prime factors, go through all divisors, and if the da[i] can be divided by the prime factor, go through all divisors in b
// //         for (int ia = 0; ia < ca.size(); ia++) for (int i = da.size() - 1; i >= 0; i--) if (da[i] % pa[ia] == 0) for (int j = db.size() - 1; j >= 0; j--)
// //         {
// //             p[i - ca[ia]][j] += p[i][j]; //p[X][Y] = p[pX][Y], cascading through the values 
// //             d[i - ca[ia]][j] += d[i][j]; 
// //         }
// //         for (int ib = 0; ib < cb.size(); ib++) for (int i = db.size() - 1; i >= 0; i--) if (db[i] % pb[ib] == 0) for (int j = da.size() - 1; j >= 0; j--)
// //         {
// //             p[j][i - cb[ib]] += p[j][i];
// //             d[j][i - cb[ib]] += d[j][i];
// //         }
// //         for (int i = 0; i < da.size(); i++) for (int j = 0; j < db.size(); j++) if (p[i][j] >= n - 1)
// //             v.push_back({ d[i][j] + (it ? c[0] : 0ll), da[i] + db[j] });
// //         swap(a[0], b[0]);
// //     }
// //     sort(v.begin(), v.end()); //the cost, followed by the value 
// //     for (int i = 1; i < v.size(); i++) v[i].second = max(v[i - 1].second, v[i].second);
// //     for (ll d : qu) ans.push_back(v[lower_bound(v.begin(), v.end(), make_pair(d + 1, 0)) - v.begin() - 1].second);
// //     return ans;
// // }
// // int main()
// // {
// //     ios::sync_with_stdio(false);
// //     cin.tie(0);
    
// //     int n, q;
// //     cin >> n >> q;
// //     vector<int> a(n), b(n);
// //     vector<ll> c(n), qi(q);
// //     for (int i = 0; i < n; i++) cin >> a[i];
// //     for (int i = 0; i < n; i++) cin >> b[i];
// //     for (int i = 0; i < n; i++) cin >> c[i];
// //     for (int i = 0; i < q; i++) cin >> qi[i];
// //     vector<ll> ans = solve(n, a, b, c, qi);
// //     for (ll x : ans) cout << x << " ";
// //     cout << "\n";
// //     return 0;
// // }
// //check if it's slope trickable by printing out the values

// int main(){
//     cin.tie(0)->sync_with_stdio(0);
//     T=1;
//     foru(cnt,1,T+1){
//         vector<pll> p;
//         maxpq<ll> pa;
//         minpq<ll> pb;
//         n=x=y=a=b=ans=0;
//         cin>>n;
//         fori(0,n){
//             cin>>x>>y;
//             p.eb(x+y,x-y); //these are the new positions
//         }
//         sort(all(p)); pa.em(0); pb.em(0); //sort by y values 
//         for(auto [y,x]:p){  //why are you doing y, x
//             ans+=max(pa.top()-y-x,x-pb.top()-y,0); //we have 2 priority queues, one for left and right...we want to pick the largest left and lowest right 
//             if(!sz(pa)||pb.top()+y>x){ //the old x + y
//                 pa.em(x+y); pa.em(x+y); pb.em(pa.top()-2*y); pa.pop();
//             }
//             else{
//                 pb.em(x-y); pb.em(x-y); pa.em(pb.top()+2*y); pb.pop();
//             }
//         }
//         ans/=2;
//         cout<<ans<<nl;
//     }
//     return 0;
// }