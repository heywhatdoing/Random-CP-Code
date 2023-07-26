#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    const int t = 100;
    cin >> n;
    vector<int> a(n);
    a[n / 2] = 1;
    for (int i = 0; i < t; i++) {
        vector<int> b(n);
        for (int j = 0; j < n; j++) {
            b[j] = (a[(j - 1 + n) % n] + a[(j + 1) % n]) % 2;
            cout << b[j] << " ";
        }
        
        cout << "\n";
        a = b;
    }
}

int main() {
    solve();
}