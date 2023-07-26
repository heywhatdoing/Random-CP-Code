#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    for (int i = 0; i <= n; i++) {
        cout << i << " " << a[i] << "\n";
    }
}

int main() {
    solve();
}