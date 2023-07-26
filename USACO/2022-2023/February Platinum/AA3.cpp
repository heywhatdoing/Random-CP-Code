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
const int N = 100005;
const int LOG = 20;
const ll inf = 1e18;
const double eps = 1e-11;
int n, m, k, qq;
struct Mint {
    ll x;
    Mint() : x(0) {}
    Mint(ll x) : x((x % mod + mod) % mod) {}
    Mint &operator += (Mint rhs) {
        x += rhs.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    
    Mint &operator -= (Mint rhs) {
        x -= rhs.x;
        if (x < 0) x += mod;
        return *this;
    }
    
    Mint &operator *= (Mint rhs) {
        x = x * rhs.x % mod;
        return *this;
    }
    
    Mint friend operator + (Mint lhs, Mint rhs) {return lhs += rhs;}
    Mint friend operator - (Mint lhs, Mint rhs) {return lhs -= rhs;}
    Mint friend operator * (Mint lhs, Mint rhs) {return lhs *= rhs;}
};

const int half = (mod + 1) / 2;
int sz = 0;
Mint sum[N * 4], all[N * 4];
ll l[N], r[N], cnt[N * 4], lt[N * 4], rt[N * 4];
stack<pair<Mint, pair<ll, array<int, 3>>>> stk;
Mint f(Mint x) {
    return x * (x + 1) * half;
}

void updatenode(int v) {
    lt[v] = lt[v * 2], rt[v] = rt[v * 2 + 1];
    cnt[v] = cnt[v * 2] + cnt[v * 2 + 1], sum[v] = sum[v * 2] + sum[v * 2 + 1];
    all[v] = all[v * 2] + all[v * 2 + 1];
}

void init(int v = 1, int tl = 0, int tr = sz - 1) {
    if (tl == tr) {
        lt[v] = l[tl], rt[v] = r[tl];
        cnt[v] = r[tl] - l[tl] + 1, all[v] = f(r[tl]) - f(l[tl] - 1), sum[v] = 0;
        return;    
    }
    
    int mid = (tl + tr) / 2;
    init(v * 2, tl, mid);
    init(v * 2 + 1, mid + 1, tr);
    updatenode(v);
}

void update(ll d, int &b, int id1, int id2, int v = 1, int tl = 0, int tr = sz - 1) {
    if (b == 0 || rt[v] < d || cnt[v] == 0) return;
    int mid = (tl + tr) / 2;
    stk.push({sum[v], {cnt[v], {v, id1, id2}}});
    if (tl == tr) {
        ll len = r[tl] - l[tl] + 1;
        ll lx = l[tl] + len - cnt[v];
        ll rx = min(lx + b - 1, r[tl]);
        cnt[v] -= rx - lx + 1, b -= rx - lx + 1, sum[v] += f(rx) - f(lx - 1);
        return;
    }
    
    if (d <= lt[v]) {
        if (b >= cnt[v * 2]) {
            stk.push({sum[v * 2], {cnt[v * 2], {v * 2, id1, id2}}});
            b -= cnt[v * 2];
            sum[v * 2] = all[v * 2], cnt[v * 2] = 0;
            update(d, b, id1, id2, v * 2 + 1, mid + 1, tr);
        }
        
        else update(d, b, id1, id2, v * 2, tl, mid);
    }
    
    else {
        update(d, b, id1, id2, v * 2, tl, mid);
        update(d, b, id1, id2, v * 2 + 1, mid + 1, tr);
    }
    
    updatenode(v);
}

void solve() {
    cin >> n;
    map<ll, pi> mp;
    vector<array<ll, 4>> allranges;
    vector<ll> days(n);
    for (int i = 0; i < n; i++) {
        ll d, b;
        cin >> d >> b;
        if (mp.count(d)) {
            auto [j, bb] = mp[d];
            allranges.push_back({j, i - 1, d, bb});
        }
        
        mp[d] = {i, b}, days[i] = d;
    }
    
    sort(days.begin(), days.end());
    for (int i = 1; i < n; i++) {
        if (days[i] == days[i - 1]) continue;
        l[sz] = days[i - 1], r[sz] = days[i] - 1;
        sz++;
    }
    
    l[sz] = days[n - 1], r[sz] = inf;
    sz++;
    for (auto [d, p] : mp) {
        auto [i, b] = p;
        allranges.push_back({i, n - 1, d, b});
    }

    init();
    auto dnq = [&](auto dnq, int l, int r, vector<array<ll, 4>> ranges) -> void {
        int mid = (l + r) / 2;
        vector<array<ll, 4>> newranges;
        for (auto [lx, rx, d, b] : ranges) {
            if (l > rx || r < lx) continue;
            else if (lx <= l && rx >= r) {
                int temp = b;
                update(d, temp, l, r);
            }
            
            else {
                newranges.push_back({lx, rx, d, b});
            }
        }
        
        if (l == r) {
            cout << sum[1].x << "\n";
        }
        
        else {
            dnq(dnq, l, mid, newranges);
            dnq(dnq, mid + 1, r, newranges);
        }
        
        while (!stk.empty()) {
            auto [x, data1] = stk.top();
            auto [y, data2] = data1;
            auto [v, id1, id2] = data2;
            // dbgm(x.x, y, v, id1, id2);
            if (l != id1 || r != id2) break;
            stk.pop();
            sum[v] = x, cnt[v] = y;
        }
    };
    
    dnq(dnq, 0, n - 1, allranges);
    
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