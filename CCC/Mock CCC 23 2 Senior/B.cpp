#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100005;
int n;
void solve() {
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    ll sum1 = 0, out = 0;
    sort(a.begin(), a.end());
    auto tri = [&](ll x, ll y, ll z) -> bool {
        return x + y > z;      
    };
    
    // cout << tri(1, 1, 5) << "\n";
    auto brute = [&](ll b, ll c, ll d, ll e, ll f, ll g) {
        ll sum = b + c + d + e + f + g;
        if (tri(b, c, f) && tri(d, e, g)) out = max(out, sum);
        if (tri(b, d, f) && tri(c, e, g)) out = max(out, sum);
        if (tri(b, e, f) && tri(c, d, g)) out = max(out, sum);
        if (tri(c, d, f) && tri(b, e, g)) out = max(out, sum);
    };
    
    for (int i = 2; i < n; i++) {
        if (i >= 5 && tri(a[i - 5], a[i - 4], a[i - 3])) {
            sum1 = a[i - 5] + a[i - 4] + a[i - 3];
        }
        
        if (sum1 != 0 && tri(a[i - 2], a[i - 1], a[i])) {
            out = max(out, sum1 + a[i - 2] + a[i - 1] + a[i]);
        }
        
        if (i >= 4 && i <= n - 2) {
            brute(a[i - 4], a[i - 3], a[i - 2], a[i - 1], a[i], a[i + 1]);
            // cout << out << "\n";
        }
        
        if (i >= 3 && i <= n - 3) {
            brute(a[i - 3], a[i - 2], a[i - 1], a[i + 1], a[i], a[i + 2]);
        }
    }
    
    cout << out << "\n";
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    solve();
}