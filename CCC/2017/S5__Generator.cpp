#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void solve() {
    const int N = 1000, M = N, Q = 1000;
    cout << N << " " << M << " " << Q << "\n";
    vector<bool> used(N + 1);
    for (int i = 0; i < N; i++) {
        int x = rnd(1, M);
        used[x] = true;
        cout << x << " ";
    }
    
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << rnd(1, 7000) << " ";
    }
    
    cout << "\n";
    vector<int> l;
    for (int i = 1; i <= N; i++) {
        if (used[i]) l.push_back(i);
    }
    
    int sz = l.size();
    for (int i = 0; i < Q; i++) {
        int ty = rnd(1, 2);
        if (ty == 1) {
            int l = rnd(1, N);
            cout << "1 " << l << " " << rnd(l, N) << "\n";
        }
        
        else {
            cout << "2 " << l[rnd(0, sz - 1)] << "\n";
        }
    }
}

int main() {
    solve();
}