#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200005;
const ll inf = 1e18 + 5;
vector<int> adj[N];
ll dp[N][2], sub[N];
int n;
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
    }
    
    for (int u = n - 1; u >= 0; u--) {
        sub[u] = 1;
        ll x = 0, mx = -inf;
        vector<ll> best;
        for (int v : adj[u]) {
            sub[u] += sub[v], mx = max(mx, sub[v]);
            x += dp[v][1] + sub[v];
            best.push_back(dp[v][1] + sub[v] - dp[v][0]);
            sort(best.rbegin(), best.rend());
            if (best.size() > 2) best.pop_back();
        }
        
        if (best.size() > 0) dp[u][0] = dp[u][1] = x - best[0];
        if (best.size() > 0) dp[u][1] = min(dp[u][1], x - mx);
        if (best.size() > 1) dp[u][1] = min(dp[u][1], x - best[0] - best[1]);
    }
    
    cout << (dp[0][1] + sub[0]) * 2 << "\n";
}