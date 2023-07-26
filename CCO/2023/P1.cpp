#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int inf = 1e9;
const int mod = 1e6 + 3;
const int N = 200005;
int add(int a, int b) {
    int res = a + b;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}

int mul(int a, int b) {
    return ((ll)a * b) % mod;
}

int binaryexp(int b, int p) {
    int res = 1;
    while (p > 0) {
        if (p & 1) res = mul(res, b);
        b = mul(b, b);
        p >>= 1;
    }
    
    return res;
}

int moddiv(int a, int b) {
    return mul(a, binaryexp(b, mod - 2));
}

void print(vector<int> &a) {
    cout << "PRINTING: " << "\n";
    for (int x : a) {
        cout << x << " ";
    }
    
    cout << "\n";
}

int n, m, k;
void solve() {
    cin >> n >> k;
    int m = n - k + 1;
    vector<int> fact(n + 1), invfact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = mul(i, fact[i - 1]);
    }
    
    invfact[n] = moddiv(1, fact[n]);
    for (int i = n - 1; i >= 0; i--) {
        invfact[i] = mul(invfact[i + 1], i + 1);
    }
    
    vector<int> a(m), b(n, -1);
    bool ok = true;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < m - 1; i++) {
        int d = a[i + 1] - a[i];
        if (abs(d) > 1) ok = false;
        if (d == -1) {
            if (b[i] == 0) ok = false;
            b[i] = 1, b[i + k] = 0;
        }
        
        if (d == 0) b[i + k] = b[i];
        if (d == 1) {
            if (b[i] == 1) ok = false;
            b[i] = 0, b[i + k] = 1;
        }
    }
    
    int x = 0, y = a[0];
    for (int i = 0; i < k; i++) {
        bool flag = false;
        for (int j = i; j < n; j += k) {
            if (b[j] == -1) continue;
            y -= b[j], flag = true;
            break;
        }
        
        if (!flag) x++;
    }
    
    if (!ok || x < y) {
        cout << 0 << "\n";
        return;
    }
    
    cout << mul(fact[x], mul(invfact[y], invfact[x - y])) << "\n";
}

int main() {
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    solve();
}