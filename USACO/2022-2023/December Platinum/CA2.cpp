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
const int N=7505;
const int SIZ=N*2+5;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
int a[N], bit1[SIZ], bit2[SIZ], cur=0, added=0;
void add(int *bit, int p, int x) {
	while (p<SIZ) {
		bit[p]+=x;
		p+=p&-p;
	}
}

void update(int p) {
	p+=N;
	cur+=p, added++;
    // dbg(p);
	add(bit1, p, p);
	add(bit2, p, 1);
}

int query(int *bit, int p) {
	int res=0;
	while (p>0) {
		res+=bit[p];
		p-=p&-p;
	}
	
	return res;
}

int getsum(int p) {
	p+=N;
    int full=query(bit2, p);
	int cut=added-full;
	int minus=query(bit1, p);
	int plus=full*p-minus;
    int res=cur-cut*p-minus+plus;
    // dbgm(p, cur, added, full, cut, minus, plus, res);
    // dbg(bit1);
	return res;
}

void solve() {
    cin>>s;
    n=s.size();
    vector<int> pos;
    for (int i=0; i<n; i++) {
    	if (s[i]=='G') {
    		a[i]=0;
    		pos.push_back(i);
    	}
    	
    	else {
            a[i]=1;
        }
    }
    
    ll out=0;
    // set<pi> pairs;
    auto calc = [&](int l, int r, bool odd) {
        int orig=l;
        // dbgm(l, r);
    	while (true) {
    		int lx=l-1, rx=r+1;
    		if (l!=r) update(l+r-n+1);
    		while (a[lx]==1 && lx>=0) {
    			lx--;
    		}
    		
    		while (a[rx]==1 && rx<n) {
    			rx++;
    		}
    		
    		for (int i=lx+1; i<=l; i++) {
    			for (int j=r; j<rx; j++) {
                    if (i==j) continue;
                    if (((i-j)&1) && odd) {
                        out--;
                    }
                    
    				else out+=getsum(i+j-n+1)+(odd ? abs((i+j)/2-orig) : 0);
                    // if (pairs.contains({i, j})) {
                    //     dbg("BAD");
                    // }
                    
                    // pairs.insert({i, j});
                    // dbgm(i, j, out);
    			}	
    		}
    		
            // dbgm(l, r, lx, rx, out);
    		if (lx<0 || rx>=n) break;
    		l=lx, r=rx;
    	}
    	
    	cur=0, added=0;
    	for (int i=0; i<SIZ; i++) {
    		bit1[i]=bit2[i]=0;
    	}
    };
    
    int siz=pos.size();
    for (int i=0; i<siz; i++) {
    	calc(pos[i], pos[i], true);
    	if (i!=siz-1) calc(pos[i], pos[i+1], false);
    }
    
    // dbg(pairs);
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