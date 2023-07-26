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

using u128=__uint128_t;
using i128=__int128;
const int mod=1000000007;
const int N=305;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
// distances 0 and 1 and 2 are useless for d1 and d2
int adj[N][N], adj2[N][N], out[N*N], d1[N][5], d2[N][5], d3[N][N];
pi rmv[N*N];
void solve() {
    cin>>n>>k;
    for (int i=0; i<n; i++) {
    	for (int j=0; j<n; j++) {
    		cin>>adj2[i][j];
    	}
    }
    
    for (int i=0; i<n*n; i++) {
    	out[i]=inf;
    	int u, v;
    	cin>>u>>v;
    	u--, v--;
    	rmv[i]={u, v};
    }
    
    for (int i=0; i<n; i++) {
    	for (int j=0; j<n; j++) {
    		adj[i][j]=d3[i][j]=inf;
    	}
    	
    	for (int j=0; j<5; j++) {
    		d1[i][j]=d2[i][j]=inf;
    	}
    }
    
    // dbg(adj);
    // dbg(adj2);
    // dbg(out);
    // dbg(d1);
    // dbg(d2);
    // dbg(d3);
    for (int i=n*n-1; i>0; i--) {
    	auto [u, v]=rmv[i];
    	adj[u][v]=adj2[u][v];
    	d1[v][3]=min(d1[v][3], d3[0][u]+adj[u][v]);
    	d2[u][3]=min(d2[u][3], adj[u][v]+d3[v][n-1]);
    	for (int j=0; j<n; j++) {
    		d3[j][v]=min(d3[j][v], adj[j][u]+adj[u][v]);
    		d3[u][j]=min(d3[u][j], adj[u][v]+adj[v][j]);
    		d1[j][3]=min(d1[j][3], adj[0][u]+adj[u][v]+adj[v][j]);
    		d2[j][3]=min(d2[j][3], adj[j][u]+adj[u][v]+adj[v][n-1]);
    		d1[j][4]=min(d1[j][4], adj[0][u]+adj[u][v]+d3[v][j]);
    		d1[j][4]=min(d1[j][4], d3[0][u]+adj[u][v]+adj[v][j]);
    		d1[v][4]=min(d1[v][4], adj[0][j]+d3[j][u]+adj[u][v]);
    		d2[j][4]=min(d2[j][4], d3[j][u]+adj[u][v]+adj[v][n-1]);
    		d2[j][4]=min(d2[j][4], adj[j][u]+adj[u][v]+d3[v][n-1]);
    		d2[u][4]=min(d2[u][4], adj[u][v]+d3[v][j]+adj[j][n-1]);
    		if (u==0) {
    			d1[j][3]=min(d1[j][3], adj[0][v]+d3[v][j]);
    			for (int k=0; k<n; k++) {
    				d1[j][4]=min(d1[j][4], adj[0][v]+adj[v][k]+d3[k][j]);
    			}
    		}
    		
    		if (v==n-1) {
    			d2[j][3]=min(d2[j][3], d3[j][u]+adj[u][n-1]);
    			for (int k=0; k<n; k++) {
    				d2[j][4]=min(d2[j][4], d3[j][k]+adj[k][u]+adj[u][n-1]);
    			}
    		}
    	}
    	
    	// dbg(d1);
    	// dbg(d2);
    	if (k==2) out[i-1]=d3[0][n-1];
    	else if (k==3) out[i-1]=d1[n-1][3];
     	else if (k==4) out[i-1]=d1[n-1][4];
     	else {
     		for (int j=0; j<n; j++) {
    			if (k==5) out[i-1]=min(out[i-1], d1[j][3]+d3[j][n-1]);
    			else if (k==6) out[i-1]=min(out[i-1], d1[j][3]+d2[j][3]);
    			else if (k==7) out[i-1]=min(out[i-1], d1[j][4]+d2[j][3]);
    			else if (k==8) out[i-1]=min(out[i-1], d1[j][4]+d2[j][4]);
    		}
     	}
    }
    
    for (int i=0; i<n*n; i++) {
    	cout<<(out[i]>=inf ? -1 : out[i])<<"\n";
    }
    
	
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