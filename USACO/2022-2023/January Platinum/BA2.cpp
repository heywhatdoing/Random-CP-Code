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

// using u128 = __uint128_t;
// using i128 = __int128;
const int mod = 1000000007;
const int N = 18;
const int LOG = 20;
const ll inf = 2e18 + 5;
const double eps = 1e-11;
int n, mm, k, qq;
ll d[N][N], a[N], dp[1 << N][N], sum[1 << N];
struct Line {
    ll m, b;
    Line() : m(0), b(-inf) {}
    Line(ll m, ll b) : m(m), b(b) {}
    ll eval(ll x) {
        return m * x + b;
    }
    
    ll intersect(Line l) {
        return (l.b - b) / (m - l.m); 
    }
};

void solve() {
    cin >> n >> mm;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = inf;
        }
        
        d[i][i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < mm; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        d[u][v] = w;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    
    for (int mask = 0; mask < 1 << n; mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) sum[mask] += a[i];
            dp[mask][i] = inf;
        }
    }
    
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }
    
    for (int mask = 1; mask < 1 << n; mask++) {
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) continue;
            int submask = mask ^ (1 << i);
            for (int j = 0; j < n; j++) {
                if (!((submask >> j) & 1) || d[j][i] == inf) continue;
                dp[mask][i] = min(dp[mask][i], dp[submask][j] + sum[submask] * d[j][i]);
            }
        }
    }
    
    vector<Line> hull[n];
    for (int i = 0; i < n; i++) {
        vector<pll> aa; 
        for (int mask = 1; mask < 1 << n; mask++) {
            if (dp[mask][i] == inf) continue;
            aa.push_back({sum[mask], dp[mask][i]});
        }
        
        sort(aa.begin(), aa.end());
        ll prevm = inf;
        for (auto [m, b] : aa) {
            if (m == prevm) continue;
            Line l = Line(m, -b);
            while (hull[i].size() > 1) {
                int sz = hull[i].size();
                Line l2 = hull[i][sz - 1], l3 = hull[i][sz - 2];
                if (l.intersect(l2) > l2.intersect(l3)) break;
                hull[i].pop_back();
            }
            
            hull[i].push_back(l);
            prevm = m;
        }
    }
    
    cin >> qq;
    while (qq--) {
        int s, e;
        cin >> s >> e;
        e--;
        int sz = hull[e].size();
        int l = 0, r = sz - 2, x = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (hull[e][mid].intersect(hull[e][mid + 1]) < s) {
                l = mid + 1, x = mid + 1;
            }
            
            else {
                r = mid - 1, x = mid;
            }
        }
        
        cout << hull[e][x].eval(s) << "\n";
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