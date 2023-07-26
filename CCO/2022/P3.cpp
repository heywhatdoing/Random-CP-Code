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
const int N = 200005;
const int LOG = 20;
const ll inf = 1e18 + 5;
const int inf2 = 1e9 + 5;
const double eps = 1e-11;
string s;
int n, m, qq;
ll k;
void solve() {
    cin >> n >> m >> k;
    ll mul = 1e9;
    k *= mul;
    vector<pll> a(n), b(m);
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        a[i] = {l * mul + 1, r * mul - 1};
    }
    
    for (int i = 0; i < m; i++) {
        ll l, r;
        cin >> l >> r;
        // dbg(i);
        b[i] = {l * mul + 1, r * mul - 1};
    }
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll t1 = 0, t2 = inf;
    int p1 = -1, p2 = -1, pp1 = -1, pp2 = -1, out = 0;
    for (int i = 1; i <= n + m; i++) {
        // dbg("HERE");
        ll t3 = inf, t4 = inf;
        int p3 = inf2, p4 = inf2, pp3 = inf2, pp4 = inf2;
        int l = 0, r = n - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (t1 < a[mid].first) r = mid - 1, res = mid;
            else l = mid + 1;
        }
        
        if (res != -1) t3 = a[res].first, pp3 = pp1, p3 = res, out = i;
        l = 0, r = m - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (t2 < b[mid].first) r = mid - 1, res = mid;
            else l = mid + 1;
        }
        
        if (res != -1) t4 = b[res].first, pp4 = pp2, p4 = res, out = i;
        l = 0; r = m - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (t1 + k < b[mid].second && pp1 < mid) r = mid - 1, res = mid;
            else l = mid + 1;
        }
        
        if (res != -1) {
            ll x = max(t1 + k + 1, b[res].first);
            if (x < t4) {
                t4 = x, pp4 = p1, p4 = res, out = i;
            }
        }
        
        l = 0, r = n - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (t2 + k < a[mid].second && pp2 < mid) r = mid - 1, res = mid;
            else l = mid + 1;
        }
        
        if (res != -1) {
            ll x = max(t2 + k + 1, a[res].first);
            if (x < t3) {
                t3 = x, pp3 = p2, p3 = res, out = i;
            }
        }
        
        t1 = t3, t2 = t4, p1 = p3, p2 = p4, pp1 = pp3, pp2 = pp4;
        // dbgm(i, t1, t2, p1, p2, pp1, pp2);
    }
    
    cout << out << "\n";
    
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