#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> m >> n;
    set<int> s;
    for (int i = 1; i <= m; i++) {
        s.insert(i);
    }
    
    int out = n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = s.upper_bound(x);
        if (it == s.begin()) {
            out = i;
            break;
        }
        
        it--;
        s.erase(it);
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}