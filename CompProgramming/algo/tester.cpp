#include <bits/stdc++.h> // Includes all standard C++ libraries (common in competitive programming).
using namespace std;
 
#define f first  // Shortcut for accessing the first element of a pair.
#define s second // Shortcut for accessing the second element of a pair.

typedef long long ll; // Defining a shorter alias for "long long" as ll.
const int MOD = 1e9+7; // A large prime number used for modular arithmetic (commonly used modulus).
const int MX = 1e5+5;  // A constant to set the maximum array size (10^5 + 5).

// This function sets up input/output redirection for competitive programming problems.
// It ties standard input/output with files and syncs I/O operations for speed.
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);  // Read from s.in
	freopen((s+".out").c_str(),"w",stdout); // Write to s.out
}

// This structure handles modular arithmetic for integers.
// It supports addition, subtraction, multiplication modulo MOD.
struct mi {
 	int v; explicit operator int() const { return v; }  // Conversion operator to int.
	mi() { v = 0; } // Default constructor initializes value to 0.
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; } // Constructor handles negative values modulo MOD.
};

// Overloading += operator to add two modular integers.
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; // If sum exceeds MOD, reduce by MOD.
	return a; 
}

// Overloading -= operator to subtract two modular integers.
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; // If subtraction results in a negative, add MOD.
	return a; 
}

// Overloading + operator using the above operator+=.
mi operator+(mi a, mi b) { return a += b; }

// Overloading - operator using the above operator-=.
mi operator-(mi a, mi b) { return a -= b; }

// Overloading * operator to multiply two modular integers.
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }

// Overloading *= operator using the above operator*.
mi& operator*=(mi& a, mi b) { return a = a*b; }

// Precomputing factorials, modular inverses, and inverse factorials for efficient combinatorics.
// `fac[i]` stores i!, `ifac[i]` stores (i!)^(-1) mod MOD, `invs[i]` stores i^(-1) mod MOD.
vector<int> invs, fac, ifac;
void genFac(int SZ) {
	invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ); 
	invs[1] = fac[0] = ifac[0] = 1;  // Initialize base cases.
	
	// Compute modular inverses for all integers up to SZ.
	for (int i = 2; i < SZ; ++i) 
		invs[i] = MOD-(ll)MOD/i*invs[MOD%i]%MOD;

	// Compute factorials and inverse factorials using previously computed values.
	for (int i = 1; i < SZ; ++i) {
		fac[i] = (ll)fac[i-1]*i%MOD;
		ifac[i] = (ll)ifac[i-1]*invs[i]%MOD;
	}
}
// Declarations for variables and arrays.
int N, par[MX];              // `N` is the number of nodes, `par` stores parents in DFS traversal.
vector<int> adj[MX];          // `adj` stores adjacency list for the tree.
mi ans[MX];                   // `ans` stores the answers for the tree.
pair<int,int> cur[MX];        // Stores degree and path length for nodes.
vector<pair<int,pair<int,int>>> ed; // Stores edge information for processing.
set<int> con;                 // Set of connected components for merging in DSU.

// Disjoint Set Union (Union-Find) structure for managing components in the tree.
// Efficiently supports union and find operations.
struct DSU {
	vector<int> e; // `e` stores the parent or rank information.
	
	// Initialize DSU for `n` elements.
	void init(int n) { e = vector<int>(n,-1); }

	// Find the root of `x` with path compression.
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	
	// Unite sets containing `x` and `y` with union-by-rank heuristic.
	bool unite(int len, int x, int y) {
		x = get(x), y = get(y); assert(x != y);  // Get the roots of `x` and `y`.
		if (e[x] > e[y]) swap(x,y); // Union by rank: make `x` the root.
		e[x] += e[y]; e[y] = x;     // Merge `y` into `x`.
		assert(con.count(y)); 
        con.erase(y); // Remove component `y` from the set.
		cur[x].f += cur[y].f-2; cur[x].s += cur[y].s+len; // Update outgoing edge counts
		return 1;
	}
};
DSU D;  // Create an instance of the DSU structure.

// Standard depth-first search (DFS) to traverse the tree and set parent nodes.
void dfs(int x) {
	for (int t: adj[x]) if (t != par[x]) { // Visit all neighbors of `x` except its parent.
		par[t] = x;  // Set the parent of `t` as `x`.
		dfs(t);      // Recursively call DFS on `t`.
	}
}

// DFS variant to find special paths or cycles in the tree.
void dfs(int x, int lst, int d) {
	if (adj[x].size() != 2) { // If node `x` is not part of a path (degree not equal to 2).
		if (lst) ed.push_back({d,{x,lst}}); // Push path length and nodes into the edge list.
		d = 0; lst = x; // Reset distance and last node.
	}
	for (int y: adj[x]) if (y != par[x]) { // Explore neighbors that are not the parent.
		par[y] = x;
		dfs(y,lst,d+1);  // Recursively perform DFS on `y`.
	}
}
 
int main() {
	setIO("circus");  // Redirect input/output from/to "circus.in" and "circus.out".
	cin >> N;         // Read number of nodes.
	genFac(N+1);      // Precompute factorials and inverses for `N+1` elements.
	
	// Read the edges of the tree and construct the adjacency list.
	for (int i = 0; i < N-1; ++i) {
		int a,b; cin >> a >> b;
		adj[a].push_back(b), adj[b].push_back(a);
	}
	
	// Find a root node that is not part of a path (degree not equal to 2).
	int root = 1; while (adj[root].size() == 2) root ++;
	
	// Perform DFS to find paths and cycles in the tree.
	dfs(root,0,0);
	
	// Sort the edges based on length.
	sort(begin(ed),end(ed));
	
	// Initialize nodes that are not part of paths with degree information.
	for (int i = 1; i <= N; ++i) if (adj[i].size() != 2) {
		cur[i] = {adj[i].size(),0}; // Set initial degree and length for each node.
		con.insert(i); // Add the node to the set of connected components.
	}
	
	// Initialize the factorial for the full tree.
	ans[N] = fac[N];
	int ind = 0;  // Index for traversing the edge list.
	
	D.init(N+1);  // Initialize the DSU structure for `N+1` elements.
	
	// Process each possible tree size `k` from `N-1` down to 1.
	for (int k = N-1; k > 0; --k) {
		// Unite components based on edge lengths smaller than `N-1-k`. it has to be smaller because the difference is the amount of 
		while (ind < ed.size() && N-1-ed[ind].f > k) {
			D.unite(ed[ind].f,ed[ind].s.f,ed[ind].s.s);  // Merge components.
			ind ++;
		}
		// Calculate the result for the current tree size.
		mi ret = fac[k];
		for (int t: con) ret *= ifac[(N-1-k)*(cur[t].f-1)+cur[t].s];  // Adjust result using modular inverses.
		ans[k] = ret;
	}
	
	// Output the answers for all tree sizes from 1 to N.
	for (int i = 1; i <= N; ++i) cout << ans[i].v << "\n";
}
