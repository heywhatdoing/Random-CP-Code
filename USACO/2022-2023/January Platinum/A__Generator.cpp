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
    const int N = 15, Q = 15;
    cout << N << " " << Q << "\n";
    int l = 0, r = 0;
    for (int i = 0; i < N * 2; i++) {
        if (l == N) {
            cout << "R";
            r++;    
        }
        
        else if (l - 1 <= r) {
            cout << "L";
            l++;
        }
        
        else {
            int x = rnd(0, 1);
            if (x == 0) {
                cout << "L";
                l++;
            }
            
            else {
                cout << "R";
                r++;
            }
        }
    }
    
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << rnd(0, 1);
    }
    
    cout << "\n";
    for (int i = 0; i < Q; i++) {
        int x = rnd(1, N - 1);
        int y = rnd(x + 1, N);
        cout << x << " " << y << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}