#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m, t;
void solve() {
    cin >> t >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    sort(a.begin(), a.end());
    if (t == 1) sort(b.begin(), b.end());
    else sort(b.rbegin(), b.rend());
    int out = 0;
    for (int i = 0; i < n; i++) {
        out += max(a[i], b[i]);
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}