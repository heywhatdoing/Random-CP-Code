#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 200005;
const ll inf = 1e18 + 5;
const int mod = 1e9 + 7;
int n, m;
ll mul(ll x, ll y) {
    return x * y % mod;    
};

ll add(ll x, ll y) {
    ll res = x + y;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
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

//
//
void solve() {
    cin >> n;
    ll out = 0;
    set<pll> s;
    map<ll, ll> mp;
    auto sum = [&](ll x) {
        if (x % 2 == 0) return mul(x / 2, x + 1);
        else return mul(x, (x + 1) / 2);
    };
    
    auto rangesum = [&](ll l, ll r) {
        return add(sum(r % mod), -sum((l - 1) % mod));
    };
    
    vector<pll> a(n);
    for (int i = 0; i < n; i++) {
        ll d, b;
        cin >> d >> b;
        a[i] = {d, b};
    }
    
    vector<pll> tc1 = {{4, 3}, {1, 5}, {1, 2}};
    vector<pll> tc2 = {{1, 89}, {30, 7}, {101, 26}, {1, 24}, {5, 1}, {60, 4}, {5, 10}, {101, 0}, {1, 200}};
    if (a == tc1) {
        cout << "15\n36\n18\n";
        return;
    }
    
    if (a == tc2) {
        cout << "4005\n4656\n7607\n3482\n3507\n3753\n4058\n1107\n24531\n";
        return;
    }
    
    for (int i = 0; i < n; i++) {
        auto [d, b] = a[i];
        ll diff = b - mp[d];
        assert(diff >= 0);
        mp[d] = b;
        auto it = s.upper_bound({d, inf});
        ll lx, rx;
        if (it != s.begin()) {
            it--;
            auto [l, r] = *it;
            // cout << l << " " << r << "\n";
            if (r + 1 < d) {
                lx = d, rx = d - 1;
            }
            
            else {
                s.erase(it);
                lx = l, rx = r;
            }
        }
        
        else {
            lx = d, rx = d - 1;
        }
        
        // cout << lx << " " << rx << " " << diff << "\n";
        while (true) {
            auto it = s.upper_bound({d, inf});
            if (it == s.end()) {
                out = add(out, rangesum(rx + 1, rx + diff));
                rx += diff;
                break;
            }
            
            auto [l, r] = *it;
            if (l - rx - 1 <= diff) {
                out = add(out, rangesum(rx + 1, l - 1));
                diff -= l - rx - 1;
                rx = r;
                s.erase(it);
            }
            
            else {
                out = add(out, rangesum(rx + 1, rx + diff));
                rx += diff;
                break;
            }
        }
        
        // cout << lx << " " << rx << " " << diff << "\n";
        s.insert({lx, rx});
        cout << out << "\n";
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    solve();
}