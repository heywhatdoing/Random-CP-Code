#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    ll t;
    cin >> n >> t;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        a[i] = c - '0';
    }
    
    auto mul = [&](vector<int> b, vector<int> c) -> vector<int> {
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            if (b[i] == 1) {
                for (int j = 0; j < n; j++) {
                    int k = (i + j) % n;
                    res[k] = (res[k] + b[i] * c[j]) % 2;
                }
            }
        }
        
        return res;
    };
    
    p[1] = 1, p[n - 1] = 1;
    for (int i = 0; i < 63; i++) {
        if ((t >> i) & 1) a = mul(p, a);
        p = mul(p, p);
    }
    
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    
    cout << "\n";
}

int main() {
    solve();
}