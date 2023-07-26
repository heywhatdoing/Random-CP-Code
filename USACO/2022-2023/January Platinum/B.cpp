#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 20;
const ll inf = 1e18 + 5;
int n, m, qq;
ll a[N], adj[N][N], dis[N][N];
bool used[N][N];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = inf, dis[i][j] = inf;
        }
    }
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1][v - 1] = w;
    }
    
    for (int i = 0; i < n; i++) {
        dis[i][i] = 0;
        for (int j = 0; j < n; j++) {
            ll mn = inf;
            int u;
            for (int k = 0; k < n; k++) {
                if (!used[i][k] && dis[i][k] < mn) {
                    mn = dis[i][k], u = k;
                }
            }
            
            used[i][u] = true;
            for (int v : adj[u]) {
                dis[i][v] = min(dis[i][v], dis[i][u] + adj[u][v]);
            }
        }
    }
    
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;
    do {
        
    }
    
    while (next_permutation(perm.begin(), perm.end()));
    cin >> qq;
    while (qq--) {
        
    }
}