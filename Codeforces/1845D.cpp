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
template <class T>
class lazysegtree {
public:
    bool ty;
    int n;
    vector<T> t, op;
    lazysegtree(bool ty, int n) {
        this->ty = ty;
        this->n = n;
        t.resize(n * 4);
        op.resize(n * 4);
    }
    
    T operation(T x, T y) {
        if (ty == 0) return min(x, y);
        else if (ty == 1) return max(x, y);
        else return x + y;
    }
    
    T returnval() {
        if (ty == 0) return inf;
        else if (ty == 1) return -inf;
        else return 0;
    }
    
    void propogate(int v, int l, int r) {
        if (op[v] == inf) return;
        int mid = (l + r) / 2;
        op[v * 2] = op[v], op[v * 2 + 1] = op[v];
        if (ty != 2) t[v * 2] = op[v], t[v * 2 + 1] = op[v];
        else t[v * 2] = op[v] * (mid - l + 1), t[v * 2 + 1] = op[v] * (r - mid);
        op[v] = inf;
    }
    
    void update(int ql, int qr, T x, int v, int tl, int tr) {
        if (tl > qr || tr < ql) return;
        if (tl >= ql && tr <= qr) {
            if (ty != 2) t[v] = x;
            else t[v] = x * (tr - tl + 1);
            op[v] = x;
            return;
        }
        
        propogate(v, tl, tr);
        int mid = (tl + tr) / 2;
        update(ql, qr, x, v * 2, tl, mid);
        update(ql, qr, x, v * 2 + 1, mid + 1, tr);
        t[v] = operation(t[v * 2], t[v * 2 + 1]);
    }
    
    void update(int ql, int qr, T x) {
        update(ql, qr, x, 1, 0, n - 1);
    }
    
    T query(int ql, int qr, int v, int tl, int tr) {
        if (tl > qr || tr < ql) return returnval();
        if (tl >= ql && tr <= qr) {
            return t[v];
        }
        
        propogate(v, tl, tr);
        int mid = (tl + tr) / 2;
        T left = query(ql, qr, v * 2, tl, mid);
        T right = query(ql, qr, v * 2 + 1, mid + 1, tr);
        return operation(left, right);
    }
    
    T query(int ql, int qr) {
        return query(ql, qr, 1, 0, n - 1);
    }
    
    // ty = 0 -> returns the rightmost value in range that is smaller than x
    // ty = 1 -> returns the rightmost value in range that is larger than x
    int findfirst(int ql, int qr, T x, int v, int tl, int tr) {
        if (tl > qr || tr < ql) return -1;
        if (ty == 0 && t[v] >= x) return -1;
        if (ty == 1 && t[v] <= x) return -1;
        if (tl == tr) return tl;
        int mid = (tl + tr) / 2;
        int right = findfirst(ql, qr, x, v * 2 + 1, mid + 1, tr);
        if (right != -1) return right;
        else return findfirst(ql, qr, x, v * 2, tl, mid);
    }
    
    int findfirst(int ql, int qr, T x) {
        return findfirst(ql, qr, x, 1, 0, n - 1);
    }
};

int n, m, k, qq;
void solve() {
    cin >> n;
    vector<ll> a(n), pref(n);
    lazysegtree<ll> st(0, n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        st.update(i, i, pref[i]);
    }
    
    ll out = 0, best = 0;
    for (int i = 0; i <= n; i++) {
        ll x = (i == 0 ? 0 : pref[i - 1]);
        int p = st.findfirst(i, n - 1, x);
        if (p == -1) p = n - 1;
        ll y = x + pref[n - 1] - pref[p];
        // dbgm(x, y, i);
        if (y > best) out = x, best = y;
    }
    
    cout << out << "\n";
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