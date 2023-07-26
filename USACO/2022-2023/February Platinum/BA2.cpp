#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 200005;
constexpr int mod = 1e9 + 7;
template<class T>
T power(T b, ll p) {
    T res = 1;
    for (; p; p >>= 1, b *= b) {
        if (p & 1) res *= b;
    }
    
    return res;
}
    
class Mint {
public:
    ll x;
    Mint() : x(0) {}
    Mint(ll x) : x(norm(x % mod)) {}
    constexpr ll norm(ll x) const {
        if (x < 0) x += mod;
        if (x >= mod) x -= mod;
        return x;    
    }
    
    Mint &operator += (Mint rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    
    Mint &operator -= (Mint rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    
    Mint &operator *= (Mint rhs) {
        x = x * rhs.x % mod;
        return *this;
    }
    
    friend Mint operator + (Mint lhs, Mint rhs) {return lhs += rhs;}
    friend Mint operator - (Mint lhs, Mint rhs) {return lhs -= rhs;}
    friend Mint operator * (Mint lhs, Mint rhs) {return lhs *= rhs;}
    Mint &operator /= (Mint rhs) {return *this *= power(rhs, mod - 2);}
    friend Mint operator / (Mint lhs, Mint rhs) {return lhs /= rhs;}
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> masks(n), cnt(1 << m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == 'H') masks[j] += (1 << i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cnt[masks[i]]++;    
    }
    
    vector<Mint> f(1 << m);
    for (int mask = 0; mask < (1 << m); mask++) {
        Mint cur = 1;
        for (int j = cnt[mask]; j >= 1; j--) {
            cur *= j;
            f[mask] += cur;
        }
    }
    
    vector<vector<Mint>> dp(1 << m, vector<Mint>(m + 1));
    for (int mask = 0; mask < (1 << m); mask++) {
        for (int i = 0; i <= m; i++) {
            dp[mask][i] = 0;
        }
    }
    
    Mint out = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        for (int i = 1; i <= m; i++) {
            if ((mask >> (i - 1)) & 1) {
                dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << (i - 1))][i - 1];
            }
            
            else {
                dp[mask][i] = dp[mask][i - 1];
            }
        }
        
        Mint res = f[mask] * (1 + dp[mask][m]);
        out += res;
        for (int i = 0; i <= m; i++) {
            dp[mask][i] += res;
        }
    }
    
    cout << out.x << "\n";
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    solve();
}