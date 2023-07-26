#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> n >> m;
    int sz = max(n, m);
    vector<int> a(sz, -1);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'S') a[i] = 0;
        else if (c == 'M') a[i] = 1;
        else a[i] = 2;
    }
    
    int out = 0;
    for (int i = 0; i < m; i++) {
        char c;
        int x;
        cin >> c >> x;
        x--;
        int val;
        if (c == 'S') val = 0;
        else if (c == 'M') val = 1;
        else val = 2;
        if (a[x] == -1) continue;
        if (a[x] >= val) {
            out++, a[x] = -1;
        }
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}