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

// using long double=__float128;
using u128=__uint128_t;
using i128=__int128;
const int mod=1000000007;
const int N=2005;
const int LOG=20;
const int inf=1e9;
const long double eps=1e-11;
int n, m, k, qq;
struct Frac {
    int x, y;
};

Frac neginf;
//returns true if a is greater than or equal to b
bool comp(Frac a, Frac b) {
    ll x=1LL*a.x*b.y, y=1LL*a.y*b.x;
    if (x>=y) return true;
    else return false;
}

Frac getmax(Frac a, Frac b) {
    if (comp(a, b)) return a;
    else return b;
}
 
Frac t[N][N*4];
int a[N];
void update(int y, int p, Frac x, int v=1, int tl=0, int tr=n-1) {
	if (tl==tr) {
		t[y][v]=x;
		return;	
	}
	
	int mid=(tl+tr)/2;
	if (p<=mid) update(y, p, x, v*2, tl, mid);
	else update(y, p, x, v*2+1, mid+1, tr);
	t[y][v]=getmax(t[y][v*2], t[y][v*2+1]);
}

Frac query(int y, int ql, int qr, int v=1, int tl=0, int tr=n-1) {
	if (ql>tr || qr<tl) return neginf;
	if (ql<=tl && qr>=tr) {
		return t[y][v];
	}
	
	int mid=(tl+tr)/2;
	return getmax(query(y, ql, qr, v*2, tl, mid), query(y, ql, qr, v*2+1, mid+1, tr));
}

int getans(int x) {
    for (int i=0; i<x; i++) {
        Frac s;
        s.x=a[x]-a[i], s.y=x-i;
        update(i, x, s);
    }
    
    for (int i=x+1; i<n; i++) {
        Frac s;
        s.x=a[i]-a[x], s.y=i-x;
        update(x, i, s);
    }
    
	int res=n-1;
	for (int i=0; i<n; i++) {
		for (int j=i+2; j<n; j++) {
            Frac s;
            s.x=a[j]-a[i], s.y=j-i;
			if (comp(s, query(i, i+1, j-1))) {
				res++;
			}
		}
	}
	
	return res;
}

void solve() {
    neginf.x=-inf, neginf.y=1;
    cin>>n;
    for (int i=0; i<n; i++) {
    	cin>>a[i];
    }
    
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            Frac s;
            s.x=a[j]-a[i], s.y=j-i;
            // dbgm(i, j, s, a[j], a[i]);
            update(i, j, s);
        }
    }
    
    cin>>qq;
    while (qq--) {
    	int x, y;
    	cin>>x>>y;
    	x--;
    	a[x]+=y;
    	cout<<getans(x)<<"\n";
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