#include <bits/stdc++.h>
using namespace std;
const int mx = 505, inf = 1e8;
int dist[mx][mx];

void solve() {
    int n, m, w; cin >> n >> m >> w;
    for (int i=0; i<mx; i++) fill(dist[i], dist[i]+mx, inf), dist[i][i] = 0;
    for (int i=0; i<m; i++) {
        int s, e, t; cin >> s >> e >> t;
        dist[--s][--e] = min(dist[s][e], t);
        dist[e][s] = dist[s][e];
    }
    
    for (int i=0; i<w; i++) {
        int s, e, t; cin >> s >> e >> t;
        dist[--s][--e] = min(dist[s][e], -t);
    }
    
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << dist[i][j] << " ";
    //     }
        
    //     cout << "\n";
    // }
    
    for (int k=0; k<n; k++) for (int i=0; i<n; i++) for (int j=0; j<n; j++) if(dist[i][k] < inf && dist[k][j] < inf)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int i=0; i<n; i++) {
        if (dist[i][i] < 0) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    int f; cin >> f;
    while (f--) solve();
}
