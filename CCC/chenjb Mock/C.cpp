#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = 1e9 + 5;
const int K = 3e6;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), pref(n, inf), suff(n, inf);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; i++) {
        pref[i] = min(a[i], (i == 0 ? inf : pref[i - 1]));
        if (i > 0) pref[i] = max(pref[i], min(a[i] + a[i - 1], (i == 1 ? inf : pref[i - 2])));
        // cout << i << " " << pref[i] << "\n";
    }
    
    for (int i = n - 1; i >= 0; i--) {
        suff[i] = min(a[i], (i == n - 1 ? inf : suff[i + 1]));
        if (i > 0) suff[i] = max(suff[i], min(a[i] + a[i + 1], (i == n - 2 ? inf : suff[i + 2])));
    }
    
    if (n <= 2) {
        cout << 0 << "\n";
        return;
    }
    
    int out = inf;
    for (int i = 0; i < n; i++) {
        int l = (i == 0 ? inf : pref[i - 1]), r = (i == n - 1 ? inf : suff[i + 1]);
        if ((a[i] >= l || l == inf) && (a[i] >= r || r == inf)) out = min(out, a[i] - min(l, r));
        cout << i << " " << l << " " << r << " " << a[i] << "\n";
        if (i < n - 1) {
            int x = a[i] + a[i + 1];
            l = (i == 0 ? inf : pref[i - 1]), r = (i == n - 2 ? inf : suff[i + 2]);
            if ((x >= l || l == inf) && (x >= r || r == inf)) out = min(out, x - min(l, r));
            cout << i << " " << l << " " << r << " " << x << "\n";
        }
        
        cout << out << "\n";
    }
    
    cout << out << "\n";
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