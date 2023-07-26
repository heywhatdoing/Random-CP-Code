#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100005;
const ll inf = 1e18 + 5;
ll n, k, a, b, c;
void solve() {
    cin >> n >> k >> a >> b >> c;
    if (a < c) swap(a, c);
    ll mx = (n - 1) * b, mn = (n - 1) * b;
    // cout << mx << " " << n << " " << k << " " << a << " " << b << " " << c << "\n";
    ll test = (n - k) * max(a, b);
    test += max((k - 1) * b, (k - 1) / 2 * (a + c) + (k % 2 == 0 ? max(c, b) : 0));
    mx = max(mx, test);
    test = (k - 1) * min(b, c);
    test += min((n - k) * b, (n - k) / 2 * (a + c) + ((n + k + 1) % 2 == 0 ? min(a, b) : 0));
    mn = min(mn, test);
    cout << mx << " " << mn << "\n";
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}