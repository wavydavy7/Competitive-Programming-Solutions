#include <bits/stdc++.h>
#include "debug.h"
using namespace std;
typedef long long ll;
#define int ll
#define rep(i,a,b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define FS first
#define SD second
#define ary(k) array<int, k>
template<class A, class B> void cmx(A &x, B y) { x = max<A>(x, y);}
template<class A, class B> void cmn(A &x, B y) { x = min<A>(x, y);}
typedef pair<int, int> pii;
typedef vector<int> vi;
string s="SATELLITE";
int n,f[99];
vector<int>A;
signed main() {
	//cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit);
	cin>>n,f[0]=1;
	for(int _=0;;_++){
		for(int i=1;i<s.size();i++)
			for(int j=s.size()-1;j;j--)
				if(s[j]==s[i])
					f[j]+=f[j-1];
		if(f[8]>n)
			break;
		A.push_back(f[8]);
	}
    debug(A);
	reverse(all(A));
	for(int i:A){
		while(n>=i)
			cout<<'S',n-=i;
		cout<<s.substr(1);
	}
	cout<<'\n';
}