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
string s, t;
int n, m, k, qq;
void solve() {
    cin >> s >> t;
    n = s.size(), m = t.size();
    vector<int> a(n), b(n);
    int cnt0 = 0, cnt1 = 0;
    int fl = t[0] == '1';
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
        a[i] ^= fl, s[i] = a[i] + '0';
        if (a[i] == 0) cnt0++;
        else cnt1++;
    }
    
    for (int i = 0; i < m; i++) {
        b[i] = t[i] - '0';
        b[i] ^= fl, t[i] = b[i] + '0';
    }
    
    vector<array<int, 3>> c;
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            c.push_back({idx, i - 1, a[idx]});
            idx = i;
        }
    }
    
    c.push_back({idx, n - 1, a[idx]});
    int sz = c.size();
    if (m == 1) {
        cout << (cnt0 == 0 ? 0 : -1) << "\n";
    }
    
    else if (m == 2) {
        int cnt00 = 0, cnt01 = 0;
        for (int i = 0; i < sz; i++) {
            auto [l, r, x] = c[i];
            if (i != 0 && x) cnt01++;
            if (!x) cnt00 += r - l;
        }
        
        if (t == "01") cout << cnt01 << "\n";
        else cout << (cnt0 - cnt1 <= 1 ? cnt00 : -1) << "\n";
    }
    
    else {
        int cnt001 = 0, cnt011 = 0, cnt010 = 0, cnt000 = 0, cnt00 = 0, odd = 0;
        for (int i = 0; i < sz; i++) {
            auto [l, r, x] = c[i];
            if (i != sz - 1 && !x && r - l > 0) cnt001++;
            if (i != 0 && x && r - l > 0) cnt011++;
            if (i != 0 && i != sz - 1 && x && r - l == 0) cnt010++;
            int len = r - l + 1;
            if (!x) cnt000 += (len - 1) / 2, cnt00 += (len + 1) / 2, odd += len % 2;
        }
        
        // dbgm(cnt000, cnt00, odd);
        if (t == "001") cout << cnt001 << "\n";
        else if (t == "011") cout << cnt011 << "\n";
        else if (t == "010") cout << (cnt010 + 1) / 2 << "\n";
        else {
            if (cnt1 == 0) {
                cout << (n < 3 ? 0 : -1) << "\n";
                return;    
            }   
                     
            int amtadd = cnt00 - cnt1 - 1, left = odd / 2;
            cout << 0 << "\n";
            // (cnt1 * 2 + 2 >= cnt0 ? -1 : cnt000)
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}