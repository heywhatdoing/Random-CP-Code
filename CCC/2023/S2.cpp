#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int N = 5005;
const int inf = 1e9 + 5;
int n, m;
int a[N], out[N], sum[N][N];
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        out[i] = inf;
    }
    
    for (int t = 0; t < n; t++) {
        for (int i = 0; i < n - t; i++) {
            int j = i + t;
            if (i == j) sum[i][j] = 0;
            else if (i + 1 == j) sum[i][j] = abs(a[i] - a[j]);
            else {
                sum[i][j] = abs(a[i] - a[j]) + sum[i + 1][j - 1];
            }
            
            // cout << i << " " << j << " " << sum[i][j] << "\n";
            out[j - i] = min(out[j - i], sum[i][j]);
        }
    }

    
    for (int i = 0; i < n; i++) {
        cout << out[i] << " ";
    }
    
    cout << "\n";
}

int main() {
    solve();
}