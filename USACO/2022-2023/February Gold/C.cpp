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
const int N = 305;
const int D = 19;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
int n, m, k, qq;
ll A, B;
int add(int x, int y) {
    int res = x + y;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}

int sub(int x, int y) {
    return add(x, -y);
}

int mul(int x, int y) {
    return 1LL * x * y % mod;
}

int comp(int x, int y) {
    if (x < y) return 0;
    else if (x == y) return 1;
    else return 2;
}

int dp[N][D][D][3], a[N], ans[N][N], d[D], inv[D];
void solveval(ll x, int mulans = 1) {
    ll cur = 100000000000000000LL;
    int sz = 0;
    for (int i = 17; i >= 0; i--) {
        d[i] = x / cur;
        if (sz == 0 && d[i] > 0) sz = i + 1;
        x %= cur, cur /= 10;
    }
    
    // dbg(d); 
    for (int i = 0; i < n; i++) {
        memset(dp, 0, sizeof(dp));
        for (int j = i; j < n; j++) {
            for (int l = 0; l < sz; l++) {
                dp[j][l][l][comp(a[j], d[l])] = 2;
            }
            
            for (int l = 0; l < sz; l++) {
                if (j == i) continue;
                for (int r = l; r < sz; r++) {
                    for (int c = 0; c < 3; c++) {
                        dp[j][l][r][c] = add(dp[j][l][r][c], dp[j - 1][l][r][c]);
                        if (l != 0) {
                            int co = comp(a[j], d[l - 1]);
                            int s = c == 1 ? co : c;
                            dp[j][l - 1][r][s] = add(dp[j][l - 1][r][s], dp[j - 1][l][r][c]);
                        }
                        
                        if (r != sz - 1) {
                            int co = comp(a[j], d[r + 1]);
                            int s = co == 1 ? c : co;
                            dp[j][l][r + 1][s] = add(dp[j][l][r + 1][s], dp[j - 1][l][r][c]);
                        }
                    }
                }
            }
            
            for (int l = 0; l < sz; l++) {
                for (int r = l; r < sz; r++) {
                    for (int c = 0; c < 3; c++) {
                        if (l == 0 && (r != sz - 1 || c < 2)) {
                            ans[i][j] = add(ans[i][j], mul(mulans, dp[j][l][r][c]));
                        }
                    }
                }
            }
        }
    }
}

void solve() {
    cin >> n >> A >> B;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    solveval(B);
    solveval(A - 1, -1);
    cin >> qq;
    while (qq--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << ans[l][r] << "\n";
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}