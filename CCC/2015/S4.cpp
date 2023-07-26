#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int inf = 1e9 + 5;
int n, m, k, A, B;
void solve() {
    cin >> k >> n >> m;
    vector<vector<int>> dis(n, vector<int>(k, inf));
    vector<vector<array<int, 3>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, t, h;
        cin >> a >> b >> t >> h;
        a--, b--;
        adj[a].push_back({b, t, h});
        adj[b].push_back({a, t, h});
    }
    
    cin >> A >> B;
    A--, B--;
    dis[A][0] = 0;
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
    q.push({0, A, 0});
    while (!q.empty()) {
        auto [d, u, hh] = q.top();
        q.pop();
        if (d != dis[u][hh]) continue;
        for (auto [v, t, h] : adj[u]) {
            int nh = hh + h;
            if (nh >= k) continue;
            if (d + t < dis[v][nh]) {
                dis[v][nh] = d + t;
                q.push({dis[v][nh], v, nh});
            }
        }
    }
    
    int out = inf;
    for (int i = 0; i < k; i++) {
        out = min(out, dis[B][i]);
    }
    
    cout << (out == inf ? -1 : out) << "\n";
}

int main() {
    solve();
}