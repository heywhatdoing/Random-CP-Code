#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 3005;
int n, k;
int getnext(int x) {
    if (x == 1) return 2;
    else return x * 3 / 2;
}

void solve() {
    cin >> n >> k;
    int sz = 1, cnt = 0;
    while (getnext(sz) <= k) {
        sz = getnext(sz), cnt++;
    }
    
    int gap = k - sz;
    int a[n][n], rmq1[n][n], rmq2[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> a[i][j];
            rmq1[i][j] = a[i][j];
        }
    }
    
    int cur = 1;
    for (int l = 1; l <= cnt; l++) {
        int x = getnext(cur);
        int gap2 = x - cur;
        for (int i = 0; i + x - 1 < n; i++) {
            for (int j = 0; j <= i; j++) {
                rmq2[i][j] = max({rmq1[i][j], rmq1[i + gap2][j], rmq1[i + gap2][j + gap2]});
            }
        }
        
        for (int i = 0; i + x - 1 < n; i++) {
            for (int j = 0; j <= i; j++) {
                rmq1[i][j] = rmq2[i][j];
            }
        }
        
        cur = x;
    }    
    
    // cout << rmq1[0][0][2] << "\n";
    // cout << sz << " " << maxlog << " " << gap << "\n";
    ll out = 0;
    for (int i = 0; i + k - 1 < n; i++) {
        for (int j = 0; j <= i; j++) {
            // cout << i << " " << j << "\n";
            out += max({rmq1[i][j], rmq1[i + gap][j], rmq1[i + gap][j + gap]});
        }
    }
    
    cout << out << "\n";
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    solve();
}