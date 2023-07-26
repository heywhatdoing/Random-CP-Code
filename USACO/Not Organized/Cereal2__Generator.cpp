#include <bits/stdc++.h>
using namespace std;

#define int long long
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l = 0, int r = 1E9) {
    if(l > r) swap(l, r);
    return std::uniform_int_distribution<int>(l, r)(rng);
    // return std::uniform_real_distribution<long double>(l, r)(rng);
}

void testcase() {
    const int N=100000, M=100000;
    cout<<M<<" "<<N<<"\n";
    for (int i=0; i<M; i++) {
        int u=rnd(1, N);
        int v=rnd(1, N);
        if (u==v) {
        	i--;
        	continue;
        }
        
        cout<<u<<" "<<v<<"\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}