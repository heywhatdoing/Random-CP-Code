#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    vector<int> cnt(26);
    for (int i = 0; i < n; i++) {
        cnt[s1[i] - 'a']++;
    }
    
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (s2[i] == '*') continue;
        cnt[s2[i] - 'a']--;
        if (cnt[s2[i] - 'a'] < 0) ok = false;
    }
    
    cout << (ok ? "A\n" : "N\n");
}

int main() {
    solve();
}