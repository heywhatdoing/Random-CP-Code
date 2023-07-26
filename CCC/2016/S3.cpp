#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> n >> m;
    vector<bool> a(n);
    int root;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a[x] = true;
        root = x;
    }
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<bool> vis(n);
    vector<int> dp(n), cnt(n);
    int nodes = 0, len = 0;
    auto dfs = [&](auto dfs, int u) -> void {
        vis[u] = true, cnt[u] = a[u];
        vector<int> cand(2, 0);
        int mx = -1;
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs(dfs, v);
                cnt[u] += cnt[v];
                if (cnt[v] > 0) {
                    cand.push_back(dp[v] + 1);
                    sort(cand.rbegin(), cand.rend());
                    cand.pop_back();
                    mx = max(mx, dp[v]);
                }
            }
        }
        
        dp[u] = mx + 1, len = max(len, cand[0] + cand[1]);
        if (cnt[u] > 0) nodes++;
    };
    
    dfs(dfs, root);
    cout << (nodes - 1) * 2 - len << "\n";
}

int main() {
    solve();
}