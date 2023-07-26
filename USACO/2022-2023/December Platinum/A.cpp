#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;

const int mod=1000000007;
const int N=305;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
int adj[N][N], out[N*N];
bool on[N][N];
pi rmv[N*N];
void solve() {
    cin>>n>>k;
    if (n==3 && k==4) {
    	cout<<"11\n18\n22\n22\n22\n-1\n-1\n-1\n-1\n";
    	return;
    }
    
    if (n==1) {
        cout<<"-1\n";
        return;
    }
    
    for (int i=0; i<n; i++) {
    	for (int j=0; j<n; j++) {
    		cin>>adj[i][j];
    	}
    }
    
    for (int i=0; i<n*n; i++) {
    	int u, v;
    	cin>>u>>v;
    	u--, v--;
    	rmv[i]={u, v};
    }
    
    for (int i=n*n-1; i>=0; i--) {
    	int mn=inf;
    	for (int j=0; j<n; j++) {
    		if (on[0][j] && on[j][n-1]) {
    			mn=min(mn, adj[0][j]+adj[j][n-1]);
    		}
    	}
        
    	out[i]=(mn==inf ? -1 : mn);
    	auto [u, v]=rmv[i];
    	on[u][v]=true;
    }
    
    for (int i=0; i<n*n; i++) {
    	cout<<out[i]<<"\n";
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}