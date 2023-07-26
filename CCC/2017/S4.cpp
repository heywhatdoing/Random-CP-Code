#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m, d;
int parent[N], sz[N];
int findset(int u) {
    while (u != parent[u]) u = parent[u];
    return u;
}

bool unionset(int u, int v) {
    int a = findset(u), b = findset(v);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a, sz[a] += sz[b];
    return true;
}

void solve() {
    cin >> n >> m >> d;
    if (n == 1) {
        cout << "0\n";
        return;    
    }
    
    for (int i = 0; i < n; i++) {
        parent[i] = i, sz[i] = 1;    
    }
    
    vector<array<int, 4>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges[i] = {w, !(i < n - 1), u, v};
    }
    
    sort(edges.begin(), edges.end());
    int left = n - 1, out = 0, last = m - 1;
    for (int i = 0; i < m; i++) {
        if (left == 1) {
            last = i;
            break;
        }
        
        auto [w, x, u, v] = edges[i];
        if (unionset(u, v)) {
            out += x, left--;
        }
    }
    
    bool ok = false;
    for (int i = last; i < m; i++) {
        auto [w, x, u, v] = edges[i];
        if (w <= d && x == 0 && unionset(u, v)) ok = true;
    }
    
    for (int i = last; i < m; i++) {
        auto [w, x, u, v] = edges[i];
            // cout << i << " " << x << "\n";
        if (findset(u) != findset(v)) {
            if (x == 0) ok = true;
            else {
                for (int j = i + 1; j < m; j++) {
                    auto [w2, x2, u2, v2] = edges[j];
                    if (w == w2 && x2 == 0 && findset(u2) != findset(v2)) ok = true;
                }
            }
            
            break;
        }
    }
    
    if (ok == false) out++;
    cout << out << "\n";
}

int main() {
    solve();
}