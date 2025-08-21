#include <bits/stdc++.h>

using namespace std;

int N, X, Y, Z;
int difl, difr;  // "lazy" update
deque<int> L, R;
long long ans;

void rig() {  // shift right A, so origin moves left
	if (L.size() == 0) L.push_back(-Y - difl); //you need to subtract difl this many times
	int t = L.back() + difl; //the true value
	L.pop_back(); 
	t = max(t, -Y); //you have the current least slope, always bounded by Y
	ans -= t;
	R.push_front(t - difr); //this is a new slope on the right side
}

void lef() {  // shift left B, so origin moves right
	if (R.size() == 0) R.push_front(X - difr);
	int t = R.front() + difr;
	R.pop_front();
	t = min(t, X);
	ans += t;
	L.push_back(t - difl); //we have new value on the left side
}

int main() {
	freopen("landscape.in", "r", stdin);
	freopen("landscape.out", "w", stdout);
	cin >> N >> X >> Y >> Z;
	for (int i = 0; i < N; ++i) {
		int A, B;
		cin >> A >> B;
		for (int j = 0; j < A; ++j)
			rig();  // or we can just do |A-B| shifts in one direction
		for (int j = 0; j < B; ++j) lef();
		difl -= Z,
		difr += Z;  // adjust slopes differently for left and right of j=0
	}
	cout << ans << "\n";
}