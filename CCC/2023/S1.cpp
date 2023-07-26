#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int N = 200005;
int n, m;
void solve() {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    int out = 0;
    for (int i = 0; i < n; i++) {
        if (a[i]) out += 3;
        if (i != 0) {
            if (a[i] && a[i - 1]) out -= 2;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (b[i]) out += 3;
        if (i != 0) {
            if (b[i] && b[i - 1]) out -= 2;
        }
        
        if (b[i] && a[i] && i % 2 == 0) out -= 2;
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}