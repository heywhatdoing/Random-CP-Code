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

#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
//const ll mod = 1e9 + 7;
const ll mod = 924844033;
// Cope Counter = 2147483647

vector<ll> adj[200001];
ll sz[200001];

ll dfs(ll i, ll p) {
  sz[i] = 1;
  for(ll j : adj[i]) {
    if(j != p) sz[i] += dfs(j, i);
  }
  return sz[i];
}
ll po(ll b, ll p) {
  ll a = 1;
  while(p > 0) {
    if(p % 2 == 1) a = a * b % mod;
    b = b * b % mod;
    p /= 2;
  }
  return a;
}

ll g = 5;
ll invg = po(5, mod - 2);
vector<ll> ntt(ll n, vector<ll> arr, bool inv) {
  vector<ll> val = arr, nxt(n);
  for(ll i = 2; i <= n; i *= 2) {
    ll omega = po((inv ? invg : g), po(2, 21) / i * 441);
    for(ll j = 0; j < n; j += i) {
      for(ll k = 0; k < i / 2; k++) {
        nxt[k + j] = (val[k + j / 2] + po(omega, k) * val[k + (j + n) / 2]) % mod;
        nxt[k + j + i / 2] = (val[k + j / 2] - po(omega, k) * val[k + (j + n) / 2] % mod + mod) % mod;
      }
    }
    val = nxt;
  }
  if(inv) {
    for(ll i = 0; i < n; i++) val[i] = val[i] * po(n, mod - 2) % mod;
  }
  return val;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll m, n = 1, u, v, ans = 0;
  cin >> m;
  vector<pair<ll, ll>> edges;
  ll frq[m + 1];
  memset(frq, 0, sizeof(frq));
  for(ll i = 0; i < m - 1; i++) {
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.push_back(mp(u, v));
  }
  dfs(0, 0);
  for(ll i = 0; i < m - 1; i++)  {
    if(sz[edges[i].f] > sz[edges[i].s]) swap(edges[i].f, edges[i].s);
    frq[sz[edges[i].f]]++, frq[m - sz[edges[i].f]]++;
  }
  while(n <= 2 * m) n *= 2;
  ll fact[n + 1], inv[n + 1];
  fact[0] = 1;
  for(ll i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % mod;
  inv[n] = po(fact[n], mod - 2);
  for(ll i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
  vector<ll> a(n, 0), b(n, 0), c(n, 0);
  for(ll i = 0; i <= m; i++) {
    a[i] = frq[i] * fact[i] % mod;
    b[i] = inv[m - i];
  }
  a = ntt(n, a, false), b = ntt(n, b, false);
  for(ll i = 0; i < n; i++) c[i] = a[i] * b[i] % mod;
  c = ntt(n, c, true);
  dbg(a);
  dbg(b);
  dbg(c);
  for(int i = 1; i <= m; i++) {
    cout << (m * fact[m] % mod * inv[i] % mod * inv[m - i] % mod - inv[i] * c[m + i] % mod + mod) % mod << "\n";
  }
}