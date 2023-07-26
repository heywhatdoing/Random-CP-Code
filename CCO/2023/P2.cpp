#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int mod = 1e6 + 3;
const int N = 1000005;
const int inf = 1e9 + 5;
int n, m, k, qq;
int t[N * 4];
void update(int p, int x, int v = 1, int tl = 0, int tr = n - 1) {
    if (tl == tr) {
        t[v] = x;
        return;    
    }
    
    int mid = (tl + tr) / 2;
    if (p <= mid) update(p, x, v * 2, tl, mid);
    else update(p, x, v * 2 + 1, mid + 1, tr);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}

int query(int ql, int qr, int v = 1, int tl = 0, int tr = n - 1) {
    if (tl > qr || tr < ql) return inf;
    if (tl >= ql && tr <= qr) {
        return t[v];
    }
    
    int mid = (tl + tr) / 2;
    int left = query(ql, qr, v * 2, tl, mid);
    int right = query(ql, qr, v * 2 + 1, mid + 1, tr);
    return min(left, right);
}

ll f(int x) {
    return 1LL * x * (x + 1) / 2;
}

ll f(int l, int r) {
    return (f(r) - f(l - 1)) % mod;
}

void print(vector<int> a) {
    cout << "PRINTING:\n";
    for (int x : a) {
        cout << x << " ";
    }
    
    cout << "\n";
}

void solve() {
    cin >> n;
    vector<int> a(n), end(n);
    int mx = 0, mxpos = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > mx) mx = a[i], mxpos = i;
        update(i, a[i]);
    }
    
    for (int i = 0; i < mxpos; i++) {
        end[i] = max((i == 0 ? 0 : end[i - 1]), a[i]);
    }
    
    for (int i = n - 1; i >= mxpos; i--) {
        end[i] = max((i == n - 1 ? 0 : end[i + 1]), a[i]);
    }
    
    // cout << f(1, 1e9) << "\n";
    // print(a);
    // print(end);
    vector<array<int, 3>> b;
    // 0 - add, 1 - rmv
    ll out = 0;
    for (int i = 0; i < n; i++) {
        b.push_back({a[i], i, 0});
        b.push_back({end[i], i, 1});
    }
    
    sort(b.begin(), b.end());
    set<int> s;
    int cur = inf;
    for (auto [x, p, t] : b) {
        // print({x, p, t});
        if (cur < x) {
            if (!s.empty()) {
                int l = *s.begin(), r = *s.rbegin();
                ll lx = query(0, l - 1), rx = query(r + 1, n - 1), cnt = x - cur;
                ll lmx = query(l + 1, n - 1), rmx = query(0, r - 1);
                // print({(int)out, x, l, r, t, p, cur});
                if (l == r) {
                    out = (out + (lx + rx) * cnt) % mod;
                }
                
                else {
                    ll c = s.size() * 2 - 3;
                    if (lx < rx) {
                        swap(lx, rx);
                        swap(lmx, rmx);
                    }
                    
                    ll y = lx + lmx + rx;
                    // cout << y * cnt << " " << f(cur + 1, x) * c << "\n";
                    out = (out + y * cnt + f(cur + 1, x) * c) % mod;
                }
            }
        }
        
        if (t == 0) {
            s.insert(p);
            update(p, inf);
        }
        
        else {
            // cout << "REMOVED:\n";
            // cout << p << "\n";
            s.erase(p);
        }
        
        cur = x;
    }
    
    for (int i = 0; i < n; i++) {
        out = (out + f(a[i], end[i] - 1)) % mod;
    }
    
    cout << out << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    solve();
}