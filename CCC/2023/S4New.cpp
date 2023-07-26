#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 2005;
const ll inf = 1e18 + 5;
int n, m;
ll dis[N][N];
ll w[N][N], cost[N][N];
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = inf, w[i][j] = -1;
        }
    }
    
    vector<vector<array<int, 3>>> adj(n);
    ll out = 0;
    for (int i = 0; i < m; i++) {
        int u, v, l, c;
        cin >> u >> v >> l >> c;
        u--, v--;
        int nu = min(u, v), nv = max(u, v);
        if (w[nu][nv] == -1 || l < w[nu][nv] || (l == w[nu][nv] && c < cost[nu][nv])) {
            w[nu][nv] = l, cost[nu][nv] = c;
        }
        
        // cout << u << " " << v << " " << w[u][v] << " " << out << "\n";
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (w[i][j] != -1) {
                adj[i].push_back({j, w[i][j], cost[i][j]});
                adj[j].push_back({i, w[i][j], cost[i][j]});
                out += cost[i][j];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        dis[i][i] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> q;
        q.push({0, i});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (d != dis[i][u]) continue;
            for (auto [v, l, c] : adj[u]) {
                if (d + l <= dis[i][v]) {
                    if (i != u) {
                        int nu = min(i, v), nv = max(i, v);
                        out -= cost[nu][nv];
                        cost[nu][nv] = 0;
                    }
                    
                    if (d + l < dis[i][v]) q.push({d + l, v});
                    dis[i][v] = d + l;
                }                
            }
        }
    }
    
    cout << out << "\n";
}

int32_t main() {
    solve();
}