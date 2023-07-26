#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 3005;
const int M = 105;
const int inf = 1e9 + 5;
int n, m;
int dp[N][M][M];
void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                dp[i][j][k] = -inf;
            }
        }
    }
    
    dp[0][0][0] = 0;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    cin >> m;
    vector<int> b(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    
    sort(b.begin(), b.end());
    dp[1][0][0] = a[1], dp[0][0][1] = (m <= 0 ? -inf : b[m]);
    int out = max(a[1], dp[0][0][1]);
    for (int p = 2; p <= n + m; p++) {
        for (int i = 0; i <= min(p, n); i++) {
            for (int j = 0; j <= min(p - i, m); j++) {
                int k = p - i - j;
                if (j + k > m) continue;
                if (i > 0) {
                    dp[i][j][k] = max({dp[i][j][k], (j <= 0 ? -inf : dp[i - 1][j - 1][k] + a[i]),
                        (k <= 0 ? -inf : dp[i - 1][j][k - 1] + a[i]), (i <= 1 ? -inf : dp[i - 2][j][k] + a[i])});
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
                }
                
                if (k > 0) {
                    dp[i][j][k] = max({dp[i][j][k], (i <= 0 ? -inf : dp[i - 1][j][k - 1] + b[m - k + 1]),
                        (j <= 0 ? -inf : dp[i][j - 1][k - 1] + b[m - k + 1])});
                }
                
                if (j > 0) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
                }
                
                out = max(out, dp[i][j][k]);
                // cout << p << " " << i << " " << j << " " << k << " " << dp[i][j][k] << "\n";
                // cout << dp[i - 2][j][k] + a[i] << "\n";
            }
        }
        
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}