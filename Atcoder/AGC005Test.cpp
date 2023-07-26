#include <bits/stdc++.h>
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
vector<ll> ntt(ll n, vector<ll> arr, bool inv) {
  vector<ll> val = arr, nxt(n);
  for(ll i = 2; i <= n; i *= 2) {
    ll omega = po(5, po(2, 21) / i * 441);
    if(inv) omega *= -1;
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
  for(int i = 1; i <= m; i++) cout << (m * fact[m] % mod * inv[i] % mod * inv[m - i] % mod - inv[i] * c[m + i] % mod + mod) % mod << "\n";
}