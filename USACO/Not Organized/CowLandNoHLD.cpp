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
const int N=100005;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
vector<vector<int>> adj(N);
vector<int> a(N), tour, startp(N), endp(N);
vector<bool> vis(N);
class LCA {
public:
    vector<int> euler, dep, first, logA;
    vector<vector<int>> rmq;
    vector<bool> vis;
    void dfs(int u) {
        vis[u]=true, first[u]=euler.size();
        euler.push_back(u);
        for (int v:adj[u]) {
            if (!vis[v]) {
                dep[v]=dep[u]+1;
                dfs(v);
                euler.push_back(u);
            }
        }
    }

    void precomp() {
        for (int i=2; i<n*2; i++) {
            logA[i]=logA[i/2]+1;
        }

        int siz=euler.size();
        for (int i=0; i<siz; i++) {
            rmq[i][0]=euler[i];
        }

        for (int j=1; j<LOG; j++) {
            for (int i=0; i+(1<<j)-1<siz; i++) {
                int r1=rmq[i][j-1], r2=rmq[i+(1<<(j-1))][j-1];
                rmq[i][j]=(dep[r1]<=dep[r2] ? r1 : r2);
            }
        }
    }

    int query(int u, int v) {
        int l=first[u], r=first[v];
        if (l>r) swap(l, r);
        int len=r-l+1;
        int maxlog=logA[len];
        int r1=rmq[l][maxlog], r2=rmq[r-(1<<maxlog)+1][maxlog];
        return (dep[r1]<=dep[r2] ? r1 : r2);
    }
    
    LCA() {
        dep.resize(n), first.resize(n), logA.resize(n*2), vis.resize(n);
        rmq=vector<vector<int>>(n*2, vector<int>(LOG));
        dfs(0);
        precomp();
    };
};

class pointsegtree {
    public:
        //change when necessary
        int neutral=0;
        vector<int> t;
        pointsegtree() {
            t.resize(n*8);
        }
        
        int operation(int x, int y) {
            //change when necessary
            return x^y;
        }
        
        void update(int x, int p, int v=1, int tl=0, int tr=n*2-1) {
            if (tl==tr) {
                t[v]=x;
                return;
            }
            
            int mid=(tl+tr)/2;
            if (p<=mid) update(x, p, v*2, tl, mid);
            else update(x, p, v*2+1, mid+1, tr);
            t[v]=operation(t[v*2], t[v*2+1]);
        }
        
        int query(int ql, int qr, int v=1, int tl=0, int tr=n*2-1) {
            if (tl>qr || tr<ql) return neutral;
            if (tl>=ql && tr<=qr) {
                return t[v];
            }
            
            int mid=(tl+tr)/2;
            int left=query(ql, qr, v*2, tl, mid);
            int right=query(ql, qr, v*2+1, mid+1, tr);
            return operation(left, right);
        }
};

int cur=0;
void dfs(int u) {
	vis[u]=true, startp[u]=cur++;
	for (int v:adj[u]) {
		if (!vis[v]) {
			dfs(v);
		}
	}
	
	endp[u]=cur++;
}

void solve() {
	freopen("cowland.in", "r", stdin);
	freopen("cowland.out", "w", stdout);
    cin>>n>>qq;
   	for (int i=0; i<n; i++) {
   		cin>>a[i];
   	}
   	
   	for (int i=0; i<n-1; i++) {
   		int u, v;
   		cin>>u>>v;
   		u--, v--;
   		adj[u].push_back(v);
   		adj[v].push_back(u);
   	}
   	
   	dfs(0);
   	pointsegtree st;
   	for (int i=0; i<n; i++) {
   		st.update(a[i], startp[i]);
   		st.update(a[i], endp[i]);
   	}
   	
   	LCA lca;
  	// for (int i=0; i<n; i++) {
  	// 	dbgm(startp[i], endp[i]);
  	// }
  	
   	while (qq--) {
   		int t, i, j, v;
   		cin>>t;
   		if (t==1) {
   			cin>>i>>v;
   			i--;
   			a[i]=v;
   			st.update(v, startp[i]);
   			st.update(v, endp[i]);
   		}
   		
   		else {
   			cin>>i>>j;
   			i--, j--;
   			int u=lca.query(i, j);
   			// dbgm(u, a[u]);
   			cout<<(st.query(0, startp[i])^st.query(0, startp[j])^a[u])<<"\n";
   		}
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