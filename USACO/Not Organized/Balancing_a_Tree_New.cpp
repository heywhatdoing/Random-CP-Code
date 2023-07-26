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
int n, m, k, qq, B;
vector<int> adj[N], p(N);
vector<pi> a(N), range(N), range2(N), best(N), best2(N);
bool ok=true;
pi merge(pi x, pi y) {
	auto [lx, rx]=x;
	auto [ly, ry]=y;
	return {max(lx, ly), min(rx, ry)};
}

void dfs(int u, int add) {
	range[u]=a[u], range2[u]={a[u].first-add, a[u].second+add};
    bool leaf=true;
	for (int v:adj[u]) {
		dfs(v, add);
        range[u]=merge(range[u], range2[v]), range2[u]=merge(range2[u], range2[v]);
	}
	
	if (range[u].first>range[u].second) ok=false;
}

void solve() {
    cin>>n;
    for (int i=0; i<N; i++) {
    	adj[i].clear();
    }
    
    p[0]=-1;
    for (int i=1; i<n; i++) {
    	cin>>p[i];
    	p[i]--;
        adj[p[i]].push_back(i);
    }
    
    for (int i=0; i<n; i++) {
        cin>>a[i].first>>a[i].second;
    }
    
    // dbg(p);
    // dbg(a);
    // dbg(adj);
    // dbg(children);
    int l=0, r=1e9, res;
    while (l<=r) {
    	int mid=(l+r)/2;
    	ok=true;
        // dbg(mid);
    	dfs(0, mid);
        // dbgm(l, r, mid);
        // dbg(range);
    	if (ok) {
    		r=mid-1, res=mid;
    		for (int i=0; i<n; i++) {
    			best[i]=range[i], best2[i]=range2[i];
    		}
    	}
    	
    	else {
    		l=mid+1;
    	}
    }
    
    cout<<res<<"\n";
    if (B==1) {
        vector<int> out(n);
        queue<pair<int, pi>> q;
        int x=best[0].first;
        out[0]=x;
        pi firstrange={x-res, x+res};
    	for (int v:adj[0]) {
            q.push({v, firstrange});
        }
        
        while (!q.empty()) {
            auto [u, pp]=q.front();
            q.pop();
            pi r1=merge(pp, best[u]);
            x=out[u]=r1.first;
            pi r2=merge(pp, {x-res, x+res});
            for (int v:adj[u]) {
                q.push({v, r2});
            }
        }
        
        for (int i=0; i<n; i++) {
            cout<<out[i]<<(i!=n-1 ? " " : "");
        }
        
        cout<<"\n";
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
    int tt;
    cin>>tt>>B;
    // pi test1={6, 6};
    // pi test2={1, 5};
    // dbg(merge(test1, test2, 0));
    while (tt--) {
        solve();
    }
}