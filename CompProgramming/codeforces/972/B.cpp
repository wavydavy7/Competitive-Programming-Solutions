#include <bits/stdc++.h>
using namespace std;
#define pb push_back

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t; cin >> t; 

	while (t--) {
		int n, m, q; cin >> n >> m >> q;
        vector<int> tchs;
        for (int i = 0; i < m; i++){
            int x;
            cin >> x;
            tchs.pb(x);
        }
        sort(tchs.begin(), tchs.end());
        for (int i = 0; i < q; i++){
            int que;
            cin >> que;
            int loc = upper_bound(tchs.begin(), tchs.end(), que) - tchs.begin();
            if (loc == 0) cout << tchs[0] - 1 << " ";
            else if (loc == m) cout << n - tchs[m - 1] << " ";
            else cout << (tchs[loc] - tchs[loc - 1]) / 2 << " ";
        }
		cout << "\n";
	}
}
