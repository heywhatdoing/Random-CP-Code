#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = 1e9 + 5;
const int K = 3e6;
void solve() {
    int n, m;
    cin >> n;
    vector<ll> a(n), cnt(4);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    
    cin >> m;
    vector<ll> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    
    // cout << a[0] << " " << b[0] << "\n";
    ll l = 0, r = 1e15, res = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll cycle = mid / n, left = mid % n;
        vector<ll> c(4), d = b;
        for (int i = 0; i < 4; i++) c[i] = cnt[i] * cycle;
        for (int i = 0; i < left; i++) {
            c[a[i]]++;
        }
        
        // cout << c[1] << " " << mid << "\n";
        for (int i = 0; i < m; i++) {
            if (d[i] % 2 == 1) {
                if (d[i] >= 3 && c[3] > 0) d[i] -= 3, c[3]--;
            }
        }
        
        for (int i = 0; i < m; i++) {
            ll mx = min(d[i] / 6, c[3] / 2);
            c[3] -= 2 * mx, d[i] -= 6 * mx;
        }
        
        for (int i = 0; i < m; i++) {
            ll mx = min(d[i] / 3, c[3]);
            c[3] -= mx, d[i] -= 3 * mx;
        }
        
        for (int i = 0; i < m; i++) {
            if (d[i] == 2 && c[3] > 0) {
                d[i] = 0, c[3]--;
            }
        }
        
        for (int i = 0; i < m; i++) {
            if (d[i] == 1 && c[3] > 0) {
                d[i] = 0, c[3]--;
            }
        }
        
        for (int i = 0; i < m; i++) {
            ll mx = min(d[i] / 2, c[2]);
            c[2] -= mx, d[i] -= 2 * mx;
        }
        
        for (int i = 0; i < m; i++) {
            if (d[i] > 0 && c[2] > 0) {
                assert(d[i] < 2);
                d[i] = 0, c[2]--;
            }
        }
        
        for (int i = 0; i < m; i++) {
            ll mx = min(d[i], c[1]);
            c[1] -= mx, d[i] -= mx;
        }
        
        bool ok = true;
        for (int i = 0; i < m; i++) {
            ok &= (d[i] == 0);
        }
        
        if (ok) {
            r = mid - 1, res = mid;
        }
        
        else {
            l = mid + 1;
        }
    }

    cout << res << "\n";
}

int main() {
    //sad
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}