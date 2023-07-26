#include <bits/stdc++.h>
using namespace std;

#define int long long
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l = 0, int r = 1E9) {
    if(l > r) swap(l, r);
    return std::uniform_int_distribution<int>(l, r)(rng);
    // return std::uniform_real_distribution<long double>(l, r)(rng);
}

typedef pair<int, int> pi;
void testcase() {
    const int N = 100000, Q = 100000;
    cout << N << " " << Q << "\n";
    for (int i = 0; i < N; i++) {
        cout << rnd(1, 1e9) << " " << rnd(1, 1e9) << " " << rnd(1, 1e9) << "\n";
    }
    
    for (int i = 0; i < Q; i++) {
        int xa = rnd(1, 1e9), ya = rnd(1, 1e9);
        int xb = rnd(xa, 1e9), yb = rnd(ya, 1e9);
        cout << xa << " " << ya << " " << xb << " " << yb << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}