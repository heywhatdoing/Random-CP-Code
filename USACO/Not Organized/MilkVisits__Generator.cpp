#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<int, int> pi;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l = 0, int r = 1E9) {
    if(l > r) swap(l, r);
    return std::uniform_int_distribution<int>(l, r)(rng);
    // return std::uniform_real_distribution<long double>(l, r)(rng);
}

void testcase() {
    const int N=200;
    const int Q=200;
    cout<<N<<" "<<Q<<"\n";
    for (int i=1; i<=N; i++) {
    	cout<<rnd(1, N)<<" ";	
    }
    
    cout<<"\n";
    for (int i=2; i<=N; i++) {
        int u=rnd(1, i-1);
        cout<<u<<" "<<i<<"\n";
    }
    
    for (int i=1; i<=Q; i++) {
    	cout<<rnd(1, N)<<" "<<rnd(1, N)<<" "<<rnd(1, N)<<"\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    testcase();
}