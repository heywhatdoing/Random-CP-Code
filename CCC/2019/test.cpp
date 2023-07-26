#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 200005;
int getnext(int x) {
    if (x == 1) return 2;
    else return x * 3 / 2;
}

void solve() {
    int k = 3005, sz = 1, cnt = 0;
    while (getnext(sz) <= k) {
        sz = getnext(sz), cnt++;
    }
    
    cout << cnt << "\n";
}

int main() {
    solve();
}