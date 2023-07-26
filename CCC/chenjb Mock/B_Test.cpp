#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int inf = 1e9 + 5;
const int K = 1e6;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), seq(K * 2 + 5), c(K * 2 + 5);
    int cnt = 0, cur = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += K;
        if (cur != a[i]) {
            if (cur != -1) seq[cur] = max(seq[cur], cnt);
            cur = a[i], cnt = 1;
        }
        
        else cnt++;
        c[a[i]]++;
    }
    
    int out = 0;
    for (int i = 0; i <= K * 2; i++) {
        out = max(out, c[i] + (i - k >= 0 && i - k <= K * 2 ? seq[i - k] : 0));
    }
    
    cout << out << "\n";
}
 
int main() {
    //sad
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    solve();
}