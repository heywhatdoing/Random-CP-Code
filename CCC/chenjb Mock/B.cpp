#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = 1e9 + 5;
const int K = 3e6;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), c(K * 2 + 5);
    vector<vector<int>> pos(K * 2 + 5);    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += K;
        c[a[i]]++;
        pos[a[i]].push_back(i);
    }
    
    int out = 0;
    for (int i = 2e6; i <= 4e6; i++) {
        int p1 = 0, p2 = 0, mx = 0, cur = 0, j = i - k;
        if (k == 0) {
            out = max(out, c[i]);    
            continue;
        }
        
        while (p1 < pos[i].size() && p2 < pos[j].size()) {
            if (pos[i][p1] < pos[j][p2]) {
                cur = max(cur - 1, 0);
                p1++;
            }
            
            else {
                cur++;
                mx = max(mx, cur);
                p2++;
            }
        }
        
        cur += pos[j].size() - p2;
        mx = max(cur, mx);
        out = max(out, c[i] + mx);
    }
    
    cout << out << "\n";
}

int main() {
    //sad
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    solve();
}