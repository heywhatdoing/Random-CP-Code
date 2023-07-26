#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 2005;
const ll inf = 1e18 + 5;
int n, m;
ll dis[N][N];
vector<pll> edges[N][N];
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = inf;
        }
    }
    
    vector<vector<array<int, 3>>> adj(n);
    ll out = 0;
    for (int i = 0; i < m; i++) {
        int u, v, l, c;
        cin >> u >> v >> l >> c;
        u--, v--;
        adj[u].push_back({v, l, c});
        adj[v].push_back({u, l, c});
        edges[min(u, v)][max(u, v)].push_back({l, c});
        out += c;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sort(edges[i][j].begin(), edges[i][j].end());
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
                        while (!edges[min(i, v)][max(i, v)].empty()) {
                            auto [l2, c2] = edges[min(i, v)][max(i, v)].back();
                            if (l2 < d + l) break;
                            out -= c2;
                            edges[min(i, v)][max(i, v)].pop_back();
                        }  
                    }
                    
                    if (d + l < dis[i][v]) q.push({d + l, v});
                    dis[i][v] = d + l;
                }                
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (auto [v, l, c] : adj[i]) {
            
        }
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}