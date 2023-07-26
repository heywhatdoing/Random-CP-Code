#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 200005;
const int inf = 1e9 + 5;
const int mod = 1e9 + 7;
int n, m;
ll mul(ll x, ll y) {
    return x * y % mod;    
};

ll add(ll x, ll y) {
    return (x + y >= mod ? x + y - mod : x + y);
}

ll power(ll x, ll y) {
    ll res = 1, cur = x;
    while (y > 0) {
        if (y & 1) {
            res = mul(res, cur);
        }
        
        cur = mul(cur, cur);
        y >>= 1;
    }
    
    return res;
}

ll moddiv(ll x, ll y) {
    return power(y, mod - 2) * x % mod;    
}

void solve() {
    cin >> n >> m;
    vector<ll> fact(n + 1), invfact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    
    invfact[n] = moddiv(1, fact[n]);
    for (int i = n - 1; i >= 0; i--) {
        invfact[i] = mul(invfact[i + 1], i + 1);
        // cout << invfact[i] << "\n";
    }
    
    auto C = [&](ll x, ll y) {
        return mul(fact[x], mul(invfact[y], invfact[x - y]));    
    };
    
    vector<ll> f(1 << m), dp(1 << m, 1);
    vector<int> mm(n), cnt(1 << m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            mm[j] += (c == 'H' ? (1 << i) : 0);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cnt[mm[i]]++;
        
    }
    
    for (int mask = 0; mask < (1 << m); mask++) {
        for (int j = 1; j <= cnt[mask]; j++) {
            f[mask] = add(f[mask], mul(fact[j], C(cnt[mask], j)));
            // cout << f[mask] << " " << cnt[mask] << " " << mask << "\n";
        }
        
    }
    
    // cout << C(2, 1) << "\n";
    ll out = 0;
    dp[0] = f[0];
    for (int mask = 1; mask < (1 << m); mask++) {
        for (int i = mask; true; i = (i - 1) & mask) {
            if (i == mask) continue;
            dp[mask] = add(dp[i], dp[mask]);
            if (i == 0) break;
        }
        
        dp[mask] = mul(dp[mask], f[mask]);
    }
    
    for (int mask = 0; mask < (1 << m); mask++) {
        out = add(out, dp[mask]);
        // cout << dp[mask] << "\n";
    }
    
    cout << out << "\n";
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    solve();
}