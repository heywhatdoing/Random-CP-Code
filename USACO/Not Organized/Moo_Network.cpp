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
const int X=1000001;
const int Y=11;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
int n, m, k, qq;
int on[X][Y], parent[N], siz[N];
void makeset(int u) {
	parent[u]=u, siz[u]=1;	
}

int findset(int u) {
	while (parent[u]!=u) u=parent[u];
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

void solve() {
    cin>>n;
    vector<pi> pos(n);
    for (int i=0; i<n; i++) {
    	makeset(i);	
    }
    
    memset(on, -1, sizeof(on));
    for (int i=0; i<n; i++) {
    	int x, y;
    	cin>>x>>y;
    	pos[i]={x, y};
    	on[x][y]=i;
    }
    
   	vector<pair<int, pi>> shortdis;
    for (int i=0; i<51; i++) {
    	for (int j=0; j<11; j++) {
    		shortdis.push_back({i*i+j*j, {i, j}});
    	}
    }
    
    // dbg(on);
    sort(shortdis.begin(), shortdis.end());
    ll out=0;
    // dbg(shortdis);
    for (auto [c, p]:shortdis) {
        for (int i=0; i<n; i++) {
    		auto [dx, dy]=p;
    		auto [x, y]=pos[i];
    		int nx=x-dx, ny1=y+dy, ny2=y-dy;
    		if (nx>=0 && nx<X) {
    			if (ny1>=0 && ny1<Y) {
    				int v=on[nx][ny1];
    				if (v!=-1 && findset(i)!=findset(v)) {
                        // cout<<i<<" "<<v<<"\n";
                        // dbgm(i, v, out);
    					unionset(i, v);
    					out+=c;
    				}
    			}
    			
    			if (ny2>=0 && ny2<Y) {
    				int v=on[nx][ny2];
    				if (v!=-1 && findset(i)!=findset(v)) {
                        // cout<<i<<" "<<v<<"\n";
                        // dbgm(i, v, out);
    					unionset(i, v);
    					out+=c;
    				}
    			}
    		}
    	}
    }
    
    // dbg(out);
    vector<pi> sets(n, {inf, -inf}), usedsets;
    for (int i=0; i<n; i++) {
    	auto [x, y]=pos[i];
    	int s=findset(i);
    	sets[s].first=min(sets[s].first, x);
    	sets[s].second=max(sets[s].second, x);
    }
    
    for (int i=0; i<n; i++) {
    	if (sets[i].first!=inf) {
    		usedsets.push_back(sets[i]);
    	}
    }
    
    sort(usedsets.begin(), usedsets.end());
    for (int i=1; i<usedsets.size(); i++) {
    	int l=usedsets[i-1].second, r=usedsets[i].first;
    	ll best=1LL*inf*inf;
    	for (int j=0; j<Y; j++) {
    		for (int k=0; k<Y; k++) {
    			if (on[l][j]!=-1 && on[r][k]!=-1) {
    				best=min(best, 1LL*(r-l)*(r-l)+(j-k)*(j-k));
    			}
    		}
    	}
    	
    	out+=best;
    }
    
    cout<<out<<"\n";
	
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