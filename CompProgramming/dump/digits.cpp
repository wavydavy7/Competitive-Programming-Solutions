#include <bits/stdc++.h>
using namespace std;

#define SZ(a) (int)a.size()
#define ALL(a) a.begin(), a.end()
#define FOR(i, a, b) for (int i = (a); i<(b); ++i)
#define RFOR(i, b, a) for (int i = (b)-1; i>=(a); --i)
#define MP make_pair
#define PB push_back
#define F first
#define S second

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;

const int INF = 1e9 + 7;
const int S = 100447;
int dp[2][S][2];

void setmin(int& a, int b)
{
	if (a > b) a = b;
}

void solve()
{
	int b, n;
	cin >> b >> n;
	VI v(n);
	FOR(i, 0, n) cin >> v[n - 1 - i];
	FOR (i, 0, 2) FOR(j, 0, S) FOR(k, 0, 2) dp[i][j][k] = INF;
	dp[0][0][0] = 0;
	int nb = n * b + 1;
	FOR(i, 0, n)
	{
		int j = i & 1;
		int d = v[i];
		
        FOR(k, 0, 2)
        {
            FOR (s, 0, nb){
                if (dp[j][s][k] == INF) continue;
                
                setmin(dp[j ^ 1][s + d + k][0], dp[j][s][k]);
                setmin(dp[j ^ 1][s][1], dp[j][s][k] + b - d - k);
                
                dp[j][s][k] = INF;
            }
		}
	}
	int j = n & 1;
	int ans = nb;
	FOR(s, 0, nb)
	{
		FOR(k, 0, 2)
		{
			ans = min(ans, max(s, dp[j][s][k]));
		}
	}
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	solve();
	return 0;
}