#include "bits/stdc++.h"
typedef long long ll;
const int LIM = 200002;
using namespace std;

struct Node {
    ll val;
    Node *left, *right;

    // Constructor for internal nodes
    Node(Node *le, Node *ri) {
        this->left = le;
        this->right = ri;
        val = 0;
        if (le) val += le->val;
        if (ri) val += ri->val;
    }

    // Constructor for leaf nodes
    Node(ll x) : val(x), left(nullptr), right(nullptr) {}

    // Proper deep copy constructor
    Node(Node *cp) : val(cp->val), left(cp->left), right(cp->right) {}
};

int N, Q, cnt = 1;
ll a[LIM];
Node* roots[LIM];

// Build function with 0-based indexing
Node* build(int l, int r, ll arr[]) {
    if (l == r) return new Node(arr[l]);
    int mid = (l + r) >> 1;
    return new Node(build(l, mid, arr), build(mid + 1, r, arr));
}

// Update function with 0-based indexing
Node* update(Node* node, int st, int end, int idx, int val) {
    if (st == end) return new Node(val);
    int mid = (st + end) >> 1;
    if (idx <= mid)
        return new Node(update(node->left, st, mid, idx, val), node->right);
    else
        return new Node(node->left, update(node->right, mid + 1, end, idx, val));
}

// Query function with 0-based indexing
ll sum(Node* node, int st, int end, int l, int r) {
    if (!node || l > r) return 0;  // Added nullptr check for the node
    if (st >= l && r >= end) return node->val;
    
    int mid = (st + end) >> 1;
    
    // Safely compute the sum for the left and right children
    ll leftSum = sum(node->left, st, mid, l, min(r, mid));
    ll rightSum = sum(node->right, mid + 1, end, max(mid + 1, l), r);
    
    return leftSum + rightSum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;
    for (int i = 0; i < N; i++) {  // Changed to 0-based indexing
        cin >> a[i];
    }
    roots[cnt++] = build(0, N - 1, a);  // Changed to 0-based indexing

    while (Q--) {
        int initial;
        cin >> initial;

        if (initial == 1) {
            int k, i, x;
            cin >> k >> i >> x;
            roots[k] = update(roots[k], 0, N - 1, i - 1, x);  // Changed to 0-based indexing
        } else if (initial == 2) {
            int k, l, r;
            cin >> k >> l >> r;
            cout << sum(roots[k], 0, N - 1, l - 1, r - 1) << endl;  // Changed to 0-based indexing
        } else if (initial == 3) {
            int k;
            cin >> k;
            roots[cnt++] = new Node(roots[k]);
        }
    }

    return 0;
}
