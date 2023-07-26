#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
typedef long long ll;
int main() {
	int n;
	cin >> n;
	ll out = 1;
	for (int i = 1; i <= n; i++) {
		out = out * i % mod;
	}
	
	cout << out << "\n";
}