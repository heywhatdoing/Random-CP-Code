#include <bits/stdc++.h>
using namespace std;
template<typename T>
int SIZE(T (&t)){
    return t.size();
}

template<typename T, size_t N>
int SIZE(T (&t)[N]){
    return N;
}

string to_string(char t){
    return "'" + string({t}) + "'";
}

string to_string(bool t){
    return t ? "true" : "false";
}

string to_string(const string &t, int x1=0, int x2=1e9){
    string ret = "";
    for(int i = min(x1,SIZE(t)), _i = min(x2,SIZE(t)-1); i <= _i; ++i){
        ret += t[i];
    }
    return '"' + ret + '"';
}

string to_string(const char* t){
    string ret(t);
    return to_string(ret);
}

template<size_t N>
string to_string(const bitset<N> &t, int x1=0, int x2=1e9){
    string ret = "";
    for(int i = min(x1,SIZE(t)); i <= min(x2,SIZE(t)-1); ++i){
        ret += t[i] + '0';
    }
    return to_string(ret);
}

template<typename T, typename... Coords>
string to_string(const T (&t), int x1=0, int x2=1e9, Coords... C);

template<typename T, typename S>
string to_string(const pair<T, S> &t){
    return "(" + to_string(t.first) + ", " + to_string(t.second) + ")";
}

template<typename T, typename... Coords>
string to_string(const T (&t), int x1, int x2, Coords... C){
    string ret = "[";
    x1 = min(x1, SIZE(t));
    auto e = begin(t);
    advance(e,x1);
    for(int i = x1, _i = min(x2,SIZE(t)-1); i <= _i; ++i){
        ret += to_string(*e, C...) + (i != _i ? ", " : "");
        e = next(e);
    }
    return ret + "]";
}

template<int Index, typename... Ts>
struct print_tuple{
    string operator() (const tuple<Ts...>& t) {
        string ret = print_tuple<Index - 1, Ts...>{}(t);
        ret += (Index ? ", " : "");
        return ret + to_string(get<Index>(t));
    }
};

template<typename... Ts>
struct print_tuple<0, Ts...> {
    string operator() (const tuple<Ts...>& t) {
        return to_string(get<0>(t));
    }
};

template<typename... Ts>
string to_string(const tuple<Ts...>& t) {
    const auto Size = tuple_size<tuple<Ts...>>::value;
    return print_tuple<Size - 1, Ts...>{}(t);
}

void dbgr(){;}
template<typename Heads, typename... Tails>
void dbgr(Heads H, Tails... T){
    cout << to_string(H) << " | ";
    dbgr(T...);
}

void dbgs(){;}
template<typename Heads, typename... Tails>
void dbgs(Heads H, Tails... T){
    cout << H << " ";
    dbgs(T...);
}

/*
formatted functions:
*/

/*
consider __VA_ARGS__ as a whole:
dbgv() prints values only
dbg() prints name and values
*/
#define dbgv(...) cout << to_string(__VA_ARGS__) << endl;

#define dbg(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgv(__VA_ARGS__);
//#define dbg(...)

/*
consider __VA_ARGS__ as a sequence of arguments:
dbgr() prints values only
dbgm() prints names and values
*/
#define dbgr(...) dbgr(__VA_ARGS__); cout << endl;

#define dbgm(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgr(__VA_ARGS__);

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;

/*
000000000000000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000000000000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
                        0000000
DO IT NOW!!!
*/

const int mod=1000000007;
const int N=100010;
const int blk=350;
const int LOG=18;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, q;
vector<vector<int>> adj(N), colnodes(N);
vector<int> eulertour;
int t=0, col[N], start[N], dis[N], rmq[N*2][LOG], logA[N*2], treepref[N];
bool vis[N], poss[N];

void dfs(int u) {
	start[u]=t++, vis[u]=true;
	eulertour.push_back(u);
	for (int v:adj[u]) {
		if (!vis[v]) {
			dis[v]=dis[u]+1;
			dfs(v);
			eulertour.push_back(u);
			t++;
		}
	}
}

void dfs2(int u, int c) {
	if (col[u]==c) treepref[u]++;
	vis[u]=true;
	for (int v:adj[u]) {
		if (!vis[v]) {
			treepref[v]=treepref[u];
			dfs2(v, c);
		}
	}
}

void precomp() {
	int siz=eulertour.size();
	for (int i=0; i<siz; i++) {
		rmq[i][0]=eulertour[i];
	}
	
	for (int j=1; j<LOG; j++) {
		for (int i=0; i<siz-(1<<j)+1; i++) {
			int l=rmq[i][j-1], r=rmq[i+(1<<(j-1))][j-1];
			rmq[i][j]=(dis[l]<=dis[r] ? l : r);
		}
	}
	
	for (int i=2; i<N*2; i++) {
		logA[i]=logA[i/2]+1;
	}
}

int query(int u, int v) {
	int l=start[u], r=start[v];
	if (l>r) {
		swap(l, r);
		swap(u, v);	
	}
	
	int siz=r-l+1;
	int maxlog=logA[siz];
	int lseg=rmq[l][maxlog], rseg=rmq[r-(1<<maxlog)+1][maxlog];
	// dbgm(l, r, lseg, rseg);
	return (dis[lseg]<=dis[rseg] ? lseg : rseg);
}

void solve() {
    cin>>n>>q;
    for (int i=0; i<n; i++) {
    	cin>>col[i];
    	col[i]--;
    	colnodes[col[i]].push_back(i);
    }
    
    for (int i=0; i<n-1; i++) {
    	int u, v;
    	cin>>u>>v;
    	u--, v--;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    
    dfs(0);
    // dbg(start);
    // dbg(dis);
    precomp();
    // dbg(eulertour);
    // dbg(rmq);
    // dbg(query(2, 4));
    // dbg(dis);
    vector<vector<array<int, 3>>> queries(N);
    for (int i=0; i<q; i++) {
    	int x, y, z;
    	cin>>x>>y>>z;
    	x--, y--, z--;
    	queries[z].push_back({x, y, i});
    }
    
    for (int i=0; i<n; i++) {
    	if (colnodes[i].size()>blk) {
    		treepref[0]=0;
    		memset(vis, false, sizeof(vis));
    		dfs2(0, i);
    		// dbg(treepref);
    		for (auto [x, y, j]:queries[i]) {
    			int lca=query(x, y);
    			// dbgm(x, y, j, lca);
    			poss[j]|=treepref[x]>treepref[lca] | treepref[y]>treepref[lca] | col[lca]==i;
    		}
    	}
    	
    	else {
    		for (auto [x, y, j]:queries[i]) {
    			int lca=query(x, y);
    			for (int u:colnodes[i]) {
    				if (dis[u]>=dis[lca]) {
    					poss[j]|=query(x, u)==u | query(y, u)==u;
    				}
    			}
    		}
    	}
    }
    
    for (int i=0; i<q; i++) {
    	if (poss[i]) cout<<"1";
    	else cout<<"0";
    }
    
    cout<<"\n";
/*
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000                                     000000000000
000000000000000000000000000000000000000000000    000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000    000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000    000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000    000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000    000000000000000000000000000000000000000000000
*/

}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}