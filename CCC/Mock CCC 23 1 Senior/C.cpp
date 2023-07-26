#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 5005;
typedef long long ll;
ll dp[N][N], pref[N][N];
ll add(ll x, ll y) {
	ll res = (x + y) % mod;
	if (res < 0) res += mod;
	return res;
}

int main() {
	int n, k;
	cin >> n >> k;
	dp[1][1] = 1, pref[1][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			if (i == 1 && j == 1) continue;
			pref[i][j] = pref[i - 1][j];
			if (j - i < k && !(i != n && (i == j))) {
				dp[i][j] = add(pref[i][i], -pref[i][max(j - k - 1, 0)]);
			}
			
			pref[i][j] = add(pref[i][j], dp[i][j]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << dp[i][j] << " ";
		}	
		
		cout << "\n";
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << pref[i][j] << " ";
		}	
		
		cout << "\n";
	}
	
	cout << dp[n][n] << "\n";
}