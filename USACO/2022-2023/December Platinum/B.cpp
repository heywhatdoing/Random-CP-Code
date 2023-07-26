#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int mod=1000000007;
const int N=200005;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
int parent[N], siz[N];
void makeset(int u) {
	parent[u]=u;
	siz[u]=1;
}

int findset(int u) {
	while (u!=parent[u]) u=parent[u];
	return u;
}

void unionset(int u, int v) {
	int x=findset(u), y=findset(v);
	if (x!=y) {
		if (siz[x]<siz[y]) swap(x, y);
		parent[y]=x;
		siz[x]+=siz[y];
	}
}

vector<int> adj[N];
void solve() {
    cin>>n>>m;
    for (int i=0; i<m; i++) {
    	int u, v;
    	cin>>u>>v;
    	u--, v--;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    
    for (int i=0; i<n; i++) {
    	makeset(i);
    }
    
    ll out=0;
    for (int i=0; i<n; i++) {
    	for (int v:adj[i]) {
    		if (v<i) {
    			unionset(i, v);
    		}	
    	}
    	
    	int iset=findset(i);
    	for (int j=i+1; j<n; j++) {
    		for (int v:adj[j]) {
    			if (findset(v)==iset) {
    				out++;
    				break;
    			}
    		}
    	}
    }
    
    cout<<out-m<<"\n";
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}