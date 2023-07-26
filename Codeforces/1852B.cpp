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
const int mod = 1000000007;
const int N = 200005;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
string s;
int n, m, k, qq;
void solve() {
    cin >> n;
    vector<pi> aa(n);
    for (int i = 0; i < n; i++) {
        cin >> aa[i].first;
        aa[i].second = i;
    }
    
    sort(aa.begin(), aa.end());
    vector<int> a(n), p(n), b(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        auto [x, j] = aa[i];
        a[i] = x, p[i] = j;
        if (a[i] != 0) b[n - x]++;
        int p1 = i, p2 = n - x - 1;
        if (p1 > p2) swap(p1, p2);
        if (p1 >= 0) {
            adj[p2].push_back(p1);
            adj[p1].push_back(p2);
        }
    }
    
    bool ok = 1;
    for (int i = 0; i < n; i++) {
        b[i] += (i == 0 ? 0 : b[i - 1]);
        if (b[i] != a[i]) ok = 0;
    }
    
    if (!ok) {
        cout << "NO\n";
        return;    
    }
    
    cout << "YES\n";
    vector<int> out(n, inf);
    int cur = n, mn;
    // dbg(adj);
    auto dfs = [&](int u, int b, int c, auto dfs) -> void {
        if (b) out[p[u]] = cur - 1;
        else out[p[u]] = -cur;
        for (int v : adj[u]) {
            if (out[p[v]] == inf) {
                dfs(v, b ^ c, c, dfs);
            }
        }    
    };
    
    for (int u = n - 1; u >= 0; u--) {
        if (out[p[u]] != inf) continue;
        int cnt = 0;
        bool self = 0, nonself = 0;
        for (int v : adj[u]) {
            cnt++;
            if (u == v) self = 1;
            else nonself = 1;
        }
        
        if (cnt == 0) {
            out[p[u]] = cur;
            cur--;
            continue;    
        }
        
        if (self && !nonself) {
            out[p[u]] = -cur;
            cur--;
            continue;
        }
        
        if (self) dfs(u, 0, 0, dfs);
        else dfs(u, 1, 1, dfs);
        cur -= 2;
        // dbgm(cur, u);
        // dbg(out);
    }
    
    // dbg(cur);
    assert(cur >= 0);
    for (int i = 0; i < n; i++) {
        // assert(out[i] != 0);
        cout << out[i] << " ";
    }
    
    cout << "\n";
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}