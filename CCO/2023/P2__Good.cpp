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
// using u128 = __uint128_t;
// using i128 = __int128;
const int mod = 1e6 + 3;
const int N = 200005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
string s;
int n, m, k, qq;
ll f(int x) {
    return 1LL * x * (x + 1) / 2;
}

ll f(int l, int r) {
    return (f(r) - f(l - 1)) % mod;
}

void solve() {
    cin >> n;
    vector<int> a(n), orig(n), end(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        orig[i] = a[i];
    }
    
    ll out = 0;
    int mx = 0, mxpos = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > mx) mx = a[i], mxpos = i;
    }
    
    for (int i = 0; i < mxpos; i++) {
        end[i] = max((i == 0 ? 0 : end[i - 1]), a[i]);
    }
    
    for (int i = n - 1; i >= mxpos; i--) {
        end[i] = max((i == n - 1 ? 0 : end[i + 1]), a[i]);
    }
    
    auto findpos = [&](int l, int r, int mn) {
        int mnx = inf;
        for (int i = l; i <= r; i++) {
            if (a[i] > mn) mnx = min(mnx, a[i]);
        }    
        
        return mnx;
    };
    
    auto inc = [&](int mnpos, int mn) {
        int mnl = findpos(0, mnpos - 1, mn);
        int mnr = findpos(mnpos + 1, n - 1, mn);
        a[mnpos]++;
        out += 1LL * mnl + mnr;
        out %= mod;
    };
    
    while (true) {
        int mn = inf;
        vector<int> p;
        for (int i = 0; i < n; i++) {
            if (a[i] < end[i]) {
                if (a[i] < mn) p.clear();
                if (a[i] <= mn) {
                    mn = a[i];
                    p.push_back(i);
                }
            } 
        }
        
        if (p.empty()) break;
        int sz = p.size();
        int pl = p[0], pr = p[sz - 1];
        if (findpos(0, pl - 1, mn) < findpos(pr + 1, n - 1, mn)) swap(pl, pr);
        inc(pl, mn);
        if (pl != pr) {
            inc(pr, mn);
            for (int i = 1; i < sz - 1; i++) {
                a[p[i]]++;    
            }
            
            out += (1LL * mn * 2 + 2) * (sz - 2);
            out %= mod;
        }
    }
    
    for (int i = 0; i < n; i++) {
        out = (out + f(orig[i], end[i] - 1)) % mod;
    }
    
    cout << out << "\n";
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}