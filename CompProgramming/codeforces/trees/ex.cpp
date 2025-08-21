#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

// Maximum number of nodes in the tree and modulo constant
const int mxN = 1e5, M = 1e9+7;

// Global variables:
// n: number of vertices (and also max cows)
// dt: counter for DFS discovery time
// ds: discovery time array for vertices
// td: array mapping discovery order to vertex id
// k: loop variable for cow count (0-indexed here)
// md1: stores minimum depth in subtree from branchy nodes
// md2: stores propagated minimum depth from parent information
// d: depth of each vertex in the tree
// anc: binary lifting table for LCA queries (17 levels for up to 1e5 nodes)
// a2: final answer for each K value (after DSU computation)
// s: size of DSU component for each vertex
// p: DSU parent array
int n, dt, ds[mxN], td[mxN], k, md1[mxN], md2[mxN], d[mxN], anc[mxN][17], a2[mxN], s[mxN], p[mxN];

// Adjacency lists for the original tree and a secondary tree structure (adj2 is not used in main DSU part)
vector<int> adj[mxN], adj2[mxN];

// Precomputed arrays:
// iv: modular inverses for numbers 1 to n
// f1: factorials modulo M (0! to n!)
// f2: inverse factorials modulo M (for combinatorial adjustments)
ll iv[mxN+1], f1[mxN+1], f2[mxN+1], ans = 1;

// Boolean array for marking visited vertices (used in dfs2)
bool vis[mxN];

// Segment tree array to hold scheduled DSU merge operations for ranges of K.
// Each node in the segment tree stores a vector of pairs (as an array of 2 ints) representing an edge.
vector<ar<int, 2>> ta[1<<18];
// Stack to store DSU merge operations for rollback during segment tree processing.
vector<ar<int, 2>> st;

// ----------------- DSU Functions with Rollback -----------------

// Standard DSU "find" function: returns the representative (root) of the component containing x.
int find(int x) {
    return x ^ p[x] ? find(p[x]) : x;
}

// DSU "join" function that merges the sets containing x and y.
// It uses union-by-size and updates the global answer 'ans' using factorial values.
// Also, the merge operation is recorded on stack 'st' to allow rollback.
void join(int x, int y) {
    // Find the representative roots for x and y.
    if ((x = find(x)) == (y = find(y)))
        return;
    // Ensure that we attach the smaller component to the larger one.
    if (s[x] > s[y])
        swap(x, y);
    // Save current state to the rollback stack.
    st.push_back({x, y});
    // Merge x into y.
    p[x] = y;
    // Update the answer by multiplying by f1[s[x]] and f1[s[y]]
    ans = ans * f1[s[x]] % M * f1[s[y]] % M;
    // Update the size of the new merged component.
    s[y] += s[x];
    // Adjust answer by multiplying by f2 for the new component size.
    ans = ans * f2[s[y]] % M;
}

// ----------------- DFS and LCA Preprocessing -----------------

// dfs1: Standard DFS to compute several useful arrays and the binary lifting table.
//   - Computes depth d[u] for each vertex u.
//   - Computes md1[u]: if u is branchy (has more than 2 neighbors), then md1[u] = d[u], else
//     it's the minimum md1 value among its children.
//   - Removes parent from the adjacency list to simplify further DFS calls.
//   - Fills anc[u][i] for LCA queries and records the DFS discovery order in ds and td.
void dfs1(int u = 0, int p = -1) {
    // If current vertex u has more than 2 neighbors then set md1[u]=d[u], else mark it very high.
    md1[u] = (adj[u].size() > 2) ? d[u] : (int)1e9;
    // Remove the parent from u's adjacency list (if parent exists).
    if (~p)
        adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
    // Set first ancestor for binary lifting.
    anc[u][0] = p;
    // Build the rest of the binary lifting table.
    for (int i = 1; i < 17; ++i)
        anc[u][i] = ~anc[u][i-1] ? anc[anc[u][i-1]][i-1] : -1;
    // Recurse for all children v of u.
    for (int v : adj[u]) {
        d[v] = d[u] + 1;
        dfs1(v, u);
        // Update md1[u] to the minimum md1 value in its subtree.
        md1[u] = min(md1[u], md1[v]);
    }
    // Record discovery time and store vertex in order.
    td[ds[u] = dt++] = u;
}

// dfs3: A DFS that computes md2 for each vertex.
// md2[u] is propagated based on parent's information and branchiness.
// It uses a parameter pd which is the propagated depth value from above.
void dfs3(int u = 0, int pd = 1e9) {
    md2[u] = pd;
    // Special handling for the root (vertex 0) if it has less than 3 children.
    if (!u && adj[u].size() < 3) {
        if (adj[u].size() > 1) {
            // When there are two children, adjust pd using md1 of the sibling.
            dfs3(adj[u][0], md1[adj[u][1]] + 1);
            dfs3(adj[u][1], md1[adj[u][0]] + 1);
        } else {
            dfs3(adj[u][0], pd);
        }
    } else {
        // For non-root or branchy nodes, update pd based on the number of children.
        for (int v : adj[u])
            dfs3(v, adj[u].size() > 1 ? 1 : pd + 1);
    }
}

// dfs2: Standard DFS on the auxiliary tree (adj2) to compute component sizes.
// This function is not central to the main DSU processing but is here if needed.
int dfs2(int u) {
    int s = 1;
    vis[u] = 1;
    for (int v : adj2[u])
        if (!vis[v])
            s += dfs2(v);
    return s;
}

// lca: Computes the Least Common Ancestor (LCA) of vertices u and v using binary lifting.
// It first lifts the deeper vertex to the same depth as the shallower one, then lifts both until they meet.
int lca(int u, int v) {
    if (d[u] < d[v])
        swap(u, v);
    // Lift u up until both are at the same depth.
    for (int i = 16; ~i; --i)
        if (d[u] - (1 << i) >= d[v])
            u = anc[u][i];
    if (u == v)
        return u;
    // Lift both u and v until their ancestors are the same.
    for (int i = 16; ~i; --i)
        if (anc[u][i] ^ anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

// ----------------- Segment Tree Based DSU Range Updates -----------------

// ae (add edge): Schedules a DSU merge operation (edge) to be active for a range of K values.
//   The parameters l1 and r1 define the interval over which the edge should be applied.
//   The segment tree is implemented recursively; when the current node interval is fully covered, the edge is added.
void ae(int l1, int r1, ar<int, 2> e, int i = 1, int l2 = 0, int r2 = n - 1) {
    // If current segment is fully inside the target interval, add the edge to the segment tree node.
    if (l1 <= l2 && r2 <= r1) {
        ta[i].push_back(e);
        return;
    }
    int m2 = (l2 + r2) / 2;
    // Recurse to the left child if the left part overlaps.
    if (l1 <= m2)
        ae(l1, r1, e, 2 * i, l2, m2);
    // Recurse to the right child if the right part overlaps.
    if (m2 < r1)
        ae(l1, r1, e, 2 * i + 1, m2 + 1, r2);
}

// dc (divide and conquer): Processes the segment tree to apply scheduled DSU merge operations,
// and when reaching a leaf (a specific K value), it computes the answer for that K.
// After processing a node, DSU operations are rolled back using the stored stack.
void dc(int i = 1, int l2 = 0, int r2 = n - 1) {
    // Save the current size of the rollback stack.
    int sts = st.size();
    // Process all scheduled DSU merge operations at this segment tree node.
    for (ar<int, 2> e : ta[i])
        join(e[0], e[1]);
    // If not at a leaf, continue dividing.
    if (l2 ^ r2) {
        int m2 = (l2 + r2) / 2;
        dc(2 * i, l2, m2);
        dc(2 * i + 1, m2 + 1, r2);
    } else {
        // At a leaf: calculate answer for this specific K value.
        // Multiply the current answer by f1[k+1] (where k = l2) for adjustment.
        a2[l2] = ans * f1[l2 + 1] % M;
    }
    // Rollback the DSU operations performed in this segment.
    while (st.size() > sts) {
        int y = st.back()[1], x = st.back()[0];
        // Reverse the multiplication effect on ans using f1 and f2.
        ans = ans * f1[s[y]] % M;
        s[y] -= s[x];
        ans = ans * f2[s[x]] % M * f2[s[y]] % M;
        p[x] = x;  // Reset DSU parent for the rolled back node.
        st.pop_back();
    }
}

// ----------------- Main Function -----------------

int main() {
    ifstream cin("circus.in");
    ofstream cout("circus.out");
    
    // Read number of vertices
    cin >> n;
    // Read n-1 edges and build the tree (adjusting for 0-indexing)
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Precompute modular inverses and factorials for numbers 1 to n.
    iv[1] = 1;
    for (int i = 2; i <= n; ++i)
        iv[i] = M - M / i * iv[M % i] % M;
    f1[0] = f2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f1[i] = f1[i - 1] * i % M;
        f2[i] = f2[i - 1] * iv[i] % M;
    }
    
    // Run the first DFS from the root (vertex 0) to compute depths, md1, and build LCA table.
    dfs1();
    // Run the second DFS to compute md2 values.
    dfs3();
    
    // A vector used temporarily for processing DSU operations per vertex.
    vector<int> st;
    // Loop for scheduling DSU operations for each valid cow count k (0-indexed, so k from 0 to n-1)
    for (; k < n; ++k) {
        // Get the vertex in DFS discovery order.
        int u = td[k];
        // For each child v of u in the DFS tree (adj[u] now holds children only after parent removal)
        for (int v : adj[u]) {
            // Check if the current interval allows an edge based on md2 value.
            if (n - (md2[u] + 2) > k)
                ae(k, n - (md2[u] + 2) - 1, {u, v});
            // The code uses a temporary vector "st" here; pop back if needed.
            st.pop_back();
        }
        // If there is a previous vertex in the DFS order stored, then compute LCA.
        if (st.size()) {
            int v = st.back();
            int w = lca(u, v);
            // Compute distance between u and v using their depths and LCA.
            int d2 = d[u] + d[v] - 2 * d[w];
            // Schedule DSU merge if valid interval exists.
            if (n - d2 > k)
                ae(k, n - d2 - 1, {u, v});
        }
        // Push current vertex onto the temporary stack.
        st.push_back(u);
    }
    
    // Initialize DSU: each vertex is its own parent and component size is 1.
    iota(p, p + n, 0);
    fill(s, s + n, 1);
    
    // Process the segment tree and compute the answer for each K using DSU with rollback.
    dc();
    
    // Output the answer for each K value (note: answers for K=1 to K=n are stored in a2[0] to a2[n-1]).
    for (int i = 0; i < n; ++i)
        cout << a2[i] << "\n";
}
