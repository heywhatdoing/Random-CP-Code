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
const ll inf = 1e18;
const double eps = 1e-11;
int n, m, k, qq;
int rmq[N][LOG], a[N], logA[N];
int operation(int x, int y) {
    return x | y;
}

void precomp() {
    for (int i = 2; i <= n; i++) {
        logA[i] = logA[i >> 1] + 1;
    }
    
    for (int i = 0; i < n; i++) {
        rmq[i][0] = a[i];
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            rmq[i][j] = operation(rmq[i][j - 1], rmq[i + (1 << j - 1)][j - 1]);
        }
    }
}

int query(int l, int r) {
    int sz = r - l + 1;
    int lg = logA[sz];
    return operation(rmq[l][lg], rmq[r - (1 << lg) + 1][lg]);
}

void solve() {
    cin >> n >> qq;
    vector<pair<ll, int>> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.push_back({i + 1, a[i]});
    }
    
    precomp();
    for (int i = 1; i < n; i++) {
        int cur = a[i], amt = 0;
        while (true) {
            int l = amt, r = n - 1, res = -1, xx = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int j = i - mid, x;
                if (j >= 0) {
                    x = query(j, i);
                }
                
                else {
                    x = query(0, i) | query(j + n, n - 1);
                }
                
                // dbgm(l, r, mid, x);
                if (x > cur) r = mid - 1, res = mid, xx = x;
                else l = mid + 1;
            }
            
            // dbg(xx);
            if (res == -1) break;
            cur = xx, amt = res + 1;
            ll p = 1LL * (n - 1) * (amt - 2) + i + n;
            // dbgm(cur, amt, i, p);
            s.push_back({p, cur});
        }
    }
    
    sort(s.begin(), s.end());
    int sz = s.size();
    int val = -1;
    vector<pair<int, ll>> ss;
    for (int i = 0; i < sz; i++) {
        auto [p, x] = s[i];
        // dbgm(val, x);
        if (x <= val) continue;
        val = x;
        ss.push_back({x, p});
    }
    
    // dbg(s);
    // dbg(ss);
    while (qq--) {
        int q;
        cin >> q;
        auto it = upper_bound(ss.begin(), ss.end(), make_pair(q, inf));
        if (it == ss.end()) cout << "-1\n";
        else {
            auto [p, x] = *it;
            cout << x << "\n";
        }
    }
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