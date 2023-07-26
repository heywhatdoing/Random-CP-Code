#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100005;
int n;
bool sieve[N];
void precomp() {
    for (int i = 2; i < N; i++) {
        if (sieve[i]) continue;
        for (int j = i * 2; j < N; j += i) {
            sieve[j] = true;
        }
    }    
}

void solve() {
    cin >> n;
    int x = 0, y = 1;
    bool fib = false, comp = false;
    while (y <= 1e5) {
        if (n == y) fib = true;
        int z = x + y;
        x = y, y = z;
    }
    
    cout << (fib && sieve[n] ? "YES\n" : "NO\n");
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    precomp();
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}