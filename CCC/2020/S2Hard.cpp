#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int MX = 4000 * 4000 + 1;
bool can_escape(int M, int N, std::vector<std::vector<int>> v) {
    // cout << MX << "\n";
    bool res = false;
    int a[MX], q[MX], head[MX], move[MX], val[MX];
    bitset<MX> vis;
    memset(head, -1, sizeof(head));
    memset(move, -1, sizeof(move));
    int cur = 0;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            int p = (i - 1) * N + (j - 1), x = i * j, pos = cur++;
            if (head[x] != -1) {
                move[pos] = head[x];
            }
            
            a[p] = v[i][j], head[x] = pos, val[pos] = p;
        }
    }
    
    int l = 0, r = 1;
    q[0] = 0, vis[0] = 1;
    while (l < r) {
        int u = q[l++], x = a[u];
        while (head[x] != -1) {
            int v = val[head[x]];
            if (!vis[v]) {
                vis[v] = 1, q[r++] = v;
            }
            
            head[x] = move[head[x]];
        }
    }
    
    return vis[M * N - 1];
}

void solve() {
    cout << (can_escape(3, 4, {{0, 0, 0, 0, 0},
                  {0, 3, 10, 8, 1},
                  {0, 1, 11, 12, 12},
                  {0, 6, 2, 3, 9}}) ? "YES\n" : "NO\n");
    cout << (can_escape(3, 4, {{0, 0, 0, 0, 0},
                  {0, 1, 10, 8, 1},
                  {0, 1, 11, 12, 12},
                  {0, 6, 2, 3, 9}}) ? "YES\n" : "NO\n");
}

int main() {
    solve();
}