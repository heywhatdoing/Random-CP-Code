#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 3005;
const int M = 105;
const int inf = 1e9 + 5;
int n, m;
// int dp[N][M][M];
void solve() {
    vector<int> a(m + 1);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    for (int i = 1; i <= m; i++) {
        cout << i << " " << a[i] << "\n";
    }
}

int main() {
    solve();
}