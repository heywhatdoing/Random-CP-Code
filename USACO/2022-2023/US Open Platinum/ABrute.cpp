#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 200005;
int n, qq;
string s;
ll calc() {
    ll out = 0, cnt = 0;
    vector<ll> dp(6);
    for (int i = 0; i < n; i++) {
        dp[0]++;
        if (s[i] == 'b') {
            dp[1] += dp[0], dp[0] = 0;
        }
        
        else if (s[i] == 'e') {
            dp[2] += dp[1], dp[1] = 0, dp[0] += dp[5], cnt += dp[5], dp[5] = 0;
        }
        
        else if (s[i] == 's') {
            dp[4] += dp[3], dp[3] = dp[2], dp[2] = 0;
        }
        
        else if (s[i] == 'i') {
            dp[5] += dp[4], dp[4] = 0;
        }
        
        out += cnt;
    }
    
    return out;
}
void solve() {
    cin >> s >> qq;
    n = s.size();
    cout << calc() << "\n";
    for (int i = 0; i < qq; i++) {
        int p;
        char c;
        cin >> p >> c;
        p--;
        s[p] = c;
        cout << calc() << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}