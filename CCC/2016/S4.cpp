#include <bits/stdc++.h>
using namespace std;

const int N = 405;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
int dp[N][N], a[N];
void solve() {
    cin >> n;
    int out = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        out = max(out, a[i]);
        dp[i][i] = true;
    }
    
    for (int sz = 1; sz < n; sz++) {
        for (int i = 0; i < n - sz; i++) {
            int j = i + sz;
            int l = i, r = j;
            int x = a[i], y = a[j];
            while (true) {
                if (x == y) {
                    if (l + 1 == r) dp[i][j] |= (dp[i][l] & dp[r][j]);
                    else dp[i][j] |= (dp[i][l] & dp[l + 1][r - 1] & dp[r][j]);
                }
                
                if (l + 1 == r) break;
                if (x <= y) {
                    x += a[++l];
                }
                
                else {
                    y += a[--r];
                }
            }
            
            if (dp[i][j]) out = max(out, x + y);
        }
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}