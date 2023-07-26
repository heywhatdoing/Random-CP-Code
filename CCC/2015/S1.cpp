#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == 0) a.pop_back();
        else a.push_back(x);
    }
    
    int out = 0;
    for (int x : a) {
        out += x;
    }
    
    cout << out << "\n";
}

int main() {
    solve();
}