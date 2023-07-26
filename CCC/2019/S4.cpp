#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
const int N = 1000005;
const int inf = 1e9 + 5;
const ll infll = 1e18 + 5;
int n, k;
struct Node {
    ll val = 0, sum = 0;
    int mx = 0, lazy = inf;
};

int a[N], larger[N];
ll dp[N];
vector<Node> t(N * 4);
void updvals(int v) {
    t[v].val = max(t[v * 2].val, t[v * 2 + 1].val);
    t[v].sum = max({t[v].val + t[v].mx, t[v * 2].sum, t[v * 2 + 1].sum});
}

void propogate(int v) {
    if (t[v].lazy == inf) return;
    t[v * 2].mx = t[v * 2].lazy = t[v * 2 + 1].mx = t[v * 2 + 1].lazy = t[v].lazy, t[v].lazy = inf;
    t[v * 2].sum = max(t[v * 2].sum, t[v * 2].val + t[v * 2].mx);
    t[v * 2 + 1].sum = max(t[v * 2 + 1].sum, t[v * 2 + 1].val + t[v * 2 + 1].mx);
}

void update(int p, ll x, int v = 1, int tl = 0, int tr = n) {
    if (tl == tr) {
        t[v].val = x, t[v].sum = x + t[v].mx;
        return;
    }
    
    propogate(v);
    int mid = (tl + tr) / 2;
    if (p <= mid) update(p, x, v * 2, tl, mid);
    else update(p, x, v * 2 + 1, mid + 1, tr);
    updvals(v);
}

void updatemx(int ql, int qr, int x, int v = 1, int tl = 0, int tr = n) {
    if (ql > tr || qr < tl) return;
    if (ql <= tl && qr >= tr) {
        t[v].mx = t[v].lazy = x, t[v].sum = max(t[v].sum, x + t[v].val);
        return;
    }
    
    propogate(v);
    int mid = (tl + tr) / 2;
    updatemx(ql, qr, x, v * 2, tl, mid);
    updatemx(ql, qr, x, v * 2 + 1, mid + 1, tr);
    updvals(v);
}

ll query(int ql, int qr, int v = 1, int tl = 0, int tr = n) {
    if (ql > tr || qr < tl) return -infll;
    if (ql <= tl && qr >= tr) {
        return t[v].sum;
    }
    
    propogate(v);
    int mid = (tl + tr) / 2;
    return max(query(ql, qr, v * 2, tl, mid), query(ql, qr, v * 2 + 1, mid + 1, tr));
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    stack<int> stk;
    for (int i = n; i >= 0; i--) {
        while (!stk.empty() && a[stk.top()] < a[i]) {
            larger[stk.top()] = i;
            stk.pop();
        }
        
        stk.push(i);
    }
    
    int start = (n % k == 0 ? k : n - (n / k) * k);
    int cur = start;
    for (int i = 1; i <= n; i++) {
        int l = larger[i];
        updatemx(l, i - 1, a[i]);
        if ((i - cur) == k) cur = i;
        dp[i] = (i < start ? -infll : query(max(0, i - k), cur - 1));
        update(i, dp[i]);
    }
    
    cout << dp[n] << "\n";
}

int main() {
    solve();
}