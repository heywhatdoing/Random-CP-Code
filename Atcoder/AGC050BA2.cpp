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
const int N = 170;
const int LOG = 20;
const int inf = 1e9;
const double eps = 1e-11;
string s;
int n, m, qq;
int a[505];
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int dp[N][N][3][2], dp2[N][N][3][2];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 2; l++) {
                    dp[i][j][k][l] = dp2[i][j][k][l] = -inf;
                }
            }
        }
    }
    
    dp[0][0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        // for (int j = 0; j < N; j++) {
        //     for (int k = 0; k < N; k++) {
        //         for (int l = 0; l < 3; l++) {
        //             for (int x = 0; x < 2; x++) {
        //                 dp2[j][k][l][x] = -inf;
        //             }
        //         }
        //     }
        // }
        
        int mx = -inf;
        for (int l = 0; l < 3; l++) mx = max(mx, dp[0][0][l][0]);
        for (int l = 0; l < 3; l++) dp[0][0][l][0] = mx;
        for (int j = 0; j <= n / 3; j++) {
            for (int k = 0; k <= n / 3; k++) {
                for (int l = 0; l < 3; l++) {
                    dp2[j][k][l][0] = max(dp2[j][k][l][0], dp[j][k][l][0]);
                    dp2[j][k][l][1] = max(dp2[j][k][l][1], dp[j][k][l][1]);
                    int p = i % 3;
                    int val = (l + p) % 3;
                    if (val == 0) {
                        dp2[j + 1][k][l][0] = max({dp2[j + 1][k][l][0], dp[j][k][l][0] + a[i], dp[j][k][l][1] + a[i]});
                    }
                    
                    else if (val == 1 && j > k) {
                        dp2[j][k + 1][l][1] = max(dp2[j][k + 1][l][0], dp[j][k][l][0] + a[i]);
                    }
                    
                    else if (val == 2 && j > 0 && k > 0) {
                        dp2[j - 1][k - 1][l][0] = max({dp2[j - 1][k - 1][l][0], dp[j][k][l][0] + a[i], dp[j][k][l][1] + a[i]});
                    }
                }
            }
        }
        
        for (int j = 0; j <= n / 3; j++) {
            for (int k = 0; k <= n / 3; k++) {
                for (int l = 0; l < 3; l++) {
                    for (int x = 0; x < 2; x++) {
                        // dbgm(i, j, k, l, x, dp2[j][k][l][x]);
                    }
                }
            }
        }
        
        swap(dp, dp2);
        // dbg(dp);
    }
    
    cout << max({dp[0][0][0][0], dp[0][0][1][0], dp[0][0][2][0]}) << "\n";
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