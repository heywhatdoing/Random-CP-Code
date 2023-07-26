#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = 1e9 + 5;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) cnt++;
    }
    
    if (n == m) {
        cout << "Richman\n";
        return;
    }
    
    int left = m - cnt;
    if (left < 0) {
        cout << "Impossible\n";
        return;    
    }
    
    ll x = 0;
    int add = inf;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            if (left > 0) x += a[i], left--;
            else add = min(add, a[i] - 1);
        }
    }
    
    // cout << add << " " << x << "\n";
    cout << x + add << "\n";
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