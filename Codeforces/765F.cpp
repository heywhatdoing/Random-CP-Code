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
const int N = 300005;
const int B = 300, B2 = 179;
const int M = N / B + 1, M2 = N / B2 + 1;
const int LOG = 20;
const int inf = 1e9 + 5;
const double eps = 1e-11;
int a[N], b[N], mnp[M2], mxp[M2];
bitset<B2> bs[M2], bsrev[M2];
vector<array<int, 3>> lp[M];
int n, m, qq;
void solve() {
    cin >> n >> qq;
    vector<pi> s(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s[i] = {x, i};        
    }
    
    sort(s.begin(), s.end());
    for (int i = 0; i < n; i++) {
        auto [x, j] = s[i];
        a[i] = x, b[j] = i;
    }
    
    vector<array<int, 3>> solvebrute;
    vector<int> out(qq);
    for (int i = 0; i < qq; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int b1 = l / B, b2 = r / B;
        if (b1 == b2) solvebrute.push_back({l, r, i});
        else lp[b1].push_back({r, l, i});
    }
    
    stack<pi> stk, stkmn, stkmx;
    int mn = inf;
    auto add = [&](int p, bool addstk = 0) {
        int bx = p / B2, px = p - bx * B2, pxrev = B2 - px - 1;
        if (addstk) {
            stk.push({bx, px});
            stkmn.push({bx, mnp[bx]});
            stkmx.push({bx, mxp[bx]});
        }
        
        int pl = B2 - bsrev[bx]._Find_next(pxrev) - 1;
        int pr = bs[bx]._Find_next(px);
        if (pl != -1) mn = min(mn, abs(a[p] - a[pl + bx * B2]));
        if (pr != B2) mn = min(mn, abs(a[p] - a[pr + bx * B2]));
        bs[bx][px] = 1, bsrev[bx][pxrev] = 1;
        mnp[bx] = min(mnp[bx], p), mxp[bx] = max(mxp[bx], p);
    };
    
    auto ansquery = [&]() {
        int cur = -1;
        for (int i = 0; i < M2; i++) {
            if (mnp[i] != inf && cur != -1) {
                mn = min(mn, abs(a[cur] - a[mnp[i]]));
            }
            
            if (mnp[i] != inf) cur = mxp[i];
        }
    };
    
    auto rollback = [&]() {
        while (!stk.empty()) {
            auto [i, j] = stk.top();
            stk.pop();
            bs[i][j] = 0, bsrev[i][B2 - j - 1] = 0;    
        }
        
        while (!stkmn.empty()) {
            auto [p, x] = stkmn.top();
            stkmn.pop();
            mnp[p] = x;
        }
        
        while (!stkmx.empty()) {
            auto [p, x] = stkmx.top();
            stkmx.pop();
            mxp[p] = x;
        }
    };
    
    for (int j = 0; j < M2; j++) {
        mnp[j] = inf, mxp[j] = -inf;
    }
        
    for (auto [l, r, j] : solvebrute) {
        mn = inf;
        for (int i = l; i <= r; i++) {
            add(b[i], 1);
        }
        
        ansquery();
        out[j] = mn;
        rollback();
    }
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M2; j++) {
            bs[j].reset(), bsrev[j].reset();
            mnp[j] = inf, mxp[j] = -inf;
        }
        
        mn = inf;
        sort(lp[i].begin(), lp[i].end());
        int rx = (i + 1) * B;
        for (auto [r, l, j] : lp[i]) {
            while (rx <= r) add(b[rx++], 0);
            int cur = mn;
            for (int k = l; k < (i + 1) * B; k++) add(b[k], 1);
            ansquery();
            out[j] = mn, mn = cur;
            rollback();
        }
    }
    
    for (int i = 0; i < qq; i++) {
        cout << out[i] << "\n";
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}