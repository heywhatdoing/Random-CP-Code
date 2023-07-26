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
const int inf = 1e9;
const double eps = 1e-11;
string s;
int n, m, k, qq;
void solve() {
    cin >> n >> qq;
    queue<int> q;
    vector<int> l(n), r(n), lmost(n, -1), rmost(n, -1), special(n), pref(n);
    vector<vector<int>> up(n, vector<int>(LOG)), down(n, vector<int>(LOG));
    vector<vector<ll>> upsum(n, vector<ll>(LOG)), downsum(n, vector<ll>(LOG));
    int cur = 0;
    for (int i = 0; i < n * 2; i++) {
        char c;
        cin >> c;
        if (c == 'L') q.push(i);
        else {
            int j = q.front();
            q.pop();
            l[cur] = j, r[cur] = i;
            cur++;
        }
    }
    
    // dbg(l);
    // dbg(r);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        special[i] = c - '0';
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + special[i];
    }
    
    int lcur = -1, rcur = -1;
    for (int i = 0; i < 2 * n; i++) {
        if (lcur != n - 1 && l[lcur + 1] == i) lcur++;
        if (r[rcur + 1] == i) {
            rcur++;
            if (lcur != rcur) rmost[rcur] = lcur;
        }
    }
    
    lcur = n, rcur = n;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (rcur != 0 && r[rcur - 1] == i) rcur--;
        if (l[lcur - 1] == i) {
            lcur--;
            if (lcur != rcur) lmost[lcur] = rcur;
        }
    }
    
    for (int i = 0; i < n; i++) {
        up[i][0] = rmost[i], down[i][0] = lmost[i];
        upsum[i][0] = (rmost[i] < 0 ? 0 : pref[rmost[i]]);
        downsum[i][0] = (lmost[i] <= 0 ? 0 : pref[lmost[i] - 1]);
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n; i++) {
            if (up[i][j - 1] == -1) up[i][j] = -1;
            else {
                up[i][j] = up[up[i][j - 1]][j - 1];
                upsum[i][j] = upsum[i][j - 1] + upsum[up[i][j - 1]][j - 1];
            }
            
            if (down[i][j - 1] == -1) down[i][j] = -1;
            else {
                down[i][j] = down[down[i][j - 1]][j - 1];
                downsum[i][j] = downsum[i][j - 1] + downsum[down[i][j - 1]][j - 1];
            }
        }
    }
    
    // dbg(pref);
    // dbg(up);
    // dbg(upsum);
    // dbg(downsum);
    // dbg(lmost);
    // dbg(rmost);
    while (qq--) {
        int lx, rx;
        cin >> lx >> rx;
        lx--, rx--;
        int u = lx;
        ll out = special[lx] + special[rx];
        if (r[lx] > l[rx]) {
            cout << "1 " << out << "\n";
            continue;    
        }
        
        int curdist = 0, bestdist = 0;
        ll cur = 0, best = 0;
        for (int j = LOG - 1; j >= 0; j--) {
            int v = up[u][j];
            if (v == -1) continue;
            if (r[v] > l[rx]) {
                best = cur + upsum[u][j];
                bestdist = curdist + 1 << j;
            }
            
            else {
                cur += upsum[u][j], u = v;
                curdist += 1 << j;
            }
        }
        
        out += best;
        // cout << out << "\n";
        cur = 0, best = 0, u = rx;
        for (int j = LOG - 1; j >= 0; j--) {
            int v = down[u][j];
            if (v == -1) continue;
            if (l[v] < r[lx]) {
                best = cur + downsum[u][j];
            }
            
            else {
                cur += downsum[u][j], u = v;
            }
        }
        
        out -= best;
        cout << bestdist + 1 << " " << out << "\n";
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