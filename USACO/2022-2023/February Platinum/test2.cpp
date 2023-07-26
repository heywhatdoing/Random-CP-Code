#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 200005;
using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
template<int P>
struct Mint {
    int x;
    constexpr Mint() : x{} {}
    constexpr Mint(i64 x) : x{norm(x % P)} {}
    
    constexpr int norm(int x) const {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(P - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    constexpr Mint &operator*=(Mint rhs) {
        x = 1LL * x * rhs.x % P;
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        i64 v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<int V, int P>
constexpr Mint<P> CInv = Mint<P>(V).inv();
 
constexpr int P = 998244353;
using Z = Mint<P>;

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
    
    vector<Z> f(1 << m);
    for (int mask = 0; mask < (1 << m); mask++) {
        Z cur = 1;
        for (int j = cnt[mask]; j >= 1; j--) {
            cur *= j;
            f[mask] += cur;
        }
        
        cout << mask << " " << f[mask].x << "\n";
    }
    
    vector<vector<Z>> dp(1 << m, vector<Z>(m + 1));
    for (int mask = 0; mask < (1 << m); mask++) {
        for (int i = 0; i <= m; i++) {
            dp[mask][i] = 0;
        }
    }
    
    Z out = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        // for (int i = 1; i <= m; i++) {
        //     if ((mask >> (i - 1)) & 1) {
        //         dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << (i - 1))][i - 1];
        //     }
            
        //     else {
        //         dp[mask][i] = dp[mask][i - 1];
        //     }
        // }
        
        Z res = f[mask] * (1 + dp[mask][m]);
        cout << f[mask].x << "\n";
        cout << (1 + dp[mask][m]).x << "\n";
        cout << res.x << "\n";
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