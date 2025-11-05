#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 200005;
const int LOG = 20;

vector<int> tree[MAXN];
int up[MAXN][LOG], depth_[MAXN], tin[MAXN], tout[MAXN], timer_ = 0;
int n, q;

// DFS to setup LCA
void dfs(int u, int p) {
    tin[u] = ++timer_;
    up[u][0] = p ? p : u;
    for (int j = 1; j < LOG; ++j)
        up[u][j] = up[up[u][j - 1]][j - 1];
    for (int v : tree[u]) if (v != p) {
        depth_[v] = depth_[u] + 1;
        dfs(v, u);
    }
    tout[u] = timer_;
}

inline bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int a, int b) {
    if (is_ancestor(a, b)) return a;
    if (is_ancestor(b, a)) return b;
    for (int j = LOG - 1; j >= 0; --j)
        if (!is_ancestor(up[a][j], b))
            a = up[a][j];
    return up[a][0];
}

inline int dist(int u, int v) {
    int w = lca(u, v);
    return depth_[u] + depth_[v] - 2 * depth_[w];
}

// Build virtual tree
vector<pair<int,int>> vtree[MAXN];
vector<int> build_virtual_tree(vector<int>& nodes) {
    sort(nodes.begin(), nodes.end(), [&](int a, int b){ return tin[a] < tin[b]; });
    int m = nodes.size();
    for (int i = 0; i + 1 < m; ++i) nodes.push_back(lca(nodes[i], nodes[i + 1]));
    sort(nodes.begin(), nodes.end(), [&](int a, int b){ return tin[a] < tin[b]; });
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    vector<int> st;
    st.push_back(nodes[0]);
    for (int i = 1; i < (int)nodes.size(); ++i) {
        int v = nodes[i];
        while (!st.empty() && !is_ancestor(st.back(), v)) st.pop_back();
        int p = st.back();
        int w = dist(p, v);
        vtree[p].push_back({v, w});
        st.push_back(v);
    }
    return nodes;
}

// DFS on virtual tree to compute contribution
long long dfs_virtual(int u, long long totalSum, unordered_map<int, long long>& val, long long &ans) {
    long long s = val[u]; // sum of labels in this subtree
    for (auto [v, w] : vtree[u]) {
        long long sub = dfs_virtual(v, totalSum, val, ans);
        long long left = sub % MOD;
        long long right = (totalSum - sub) % MOD;
        if (right < 0) right += MOD;
        ans = (ans + ((left * right) % MOD) * w % MOD) % MOD;
        s += sub;
    }
    vtree[u].clear(); // clean after use
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) tree[i].clear();

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, 0);

    while (q--) {
        int k; cin >> k;
        vector<int> nodes(k);
        long long totalSum = 0;
        for (int i = 0; i < k; ++i) {
            cin >> nodes[i];
            totalSum = (totalSum + nodes[i]) % MOD;
        }
        if (k < 2) {
            cout << 0 << "\n";
            continue;
        }

        unordered_map<int, long long> val;
        for (int x : nodes) val[x] = x;

        vector<int> all = build_virtual_tree(nodes);
        long long ans = 0;
        dfs_virtual(all[0], totalSum, val, ans);
        cout << (ans % MOD + MOD) % MOD << "\n";
    }

    return 0;
}

