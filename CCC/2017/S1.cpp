#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    ll x = 0, y = 0, out = 0;
    for (int i = 0; i < n; i++) {
        x += a[i], y += b[i];
        if (x == y) out = i + 1;
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}