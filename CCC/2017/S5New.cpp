#include <bits/stdc++.h>
using namespace std;

const int N = 15;
const int blk = 2;
const int cntblk = N / blk + 2;
typedef long long ll;
typedef pair<int, int> pi;
int n, m, qq;
int l[N], a[N], cnt[N], sq[N], rot[cntblk];
int nextleft[cntblk][N], nextright[cntblk][N], sum[cntblk], id[cntblk];
vector<int> pos[N], vals[N], pref[N];
void solve() {
    cin >> n >> m >> qq;    
    memset(nextleft, -1, sizeof(nextleft));
    memset(nextright, -1, sizeof(nextright));
    memset(sq, -1, sizeof(sq));
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; i++) {
        cin >> l[i];
        cnt[--l[i]]++;
        pos[l[i]].push_back(i);
    }
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[l[i]].push_back(a[i]);
    }
    
    int cur = 0;
    for (int i = 0; i < m; i++) {
        if (cnt[i] >= blk) {
            sq[i] = cur, id[cur++] = i;
        }
    }
    
    for (int i = 0; i < m; i++) {
        pref[i].resize(cnt[i]);
        for (int j = 0; j < cnt[i]; j++) {
            // cout << i << " " << j << "\n";
            pref[i][j] = (j == 0 ? 0 : pref[i][j - 1]) + vals[i][j];
        }
    }
    
    for (int i = 0; i < cntblk; i++) {
        for (int j = i * blk; j < min((i + 1) * blk, n); j++) {
            if (sq[l[j]] == -1) sum[i] += a[j];
        }
    }
    
    for (int i = 0; i < cntblk; i++) {
        if (id[i] == -1) break;
        int prev = 0;
        // cout << "Cnt : " << cnt[id[i]] << "\n";
        for (int j = 0; j < cnt[id[i]]; j++) {
            for (int k = prev; k <= pos[id[i]][j]; k++) {
                // cout << "Val : " << pos[id[i]][j] << "\n";
                nextleft[i][k] = j;
            }
            
            prev = pos[id[i]][j] + 1;
        }
        
        prev = n - 1;
        for (int j = cnt[id[i]] - 1; j >= 0; j--) {
            for (int k = pos[id[i]][j]; k <= prev; k++) {
                nextright[i][k] = j;
            }
            
            prev = pos[id[i]][j] - 1;
        }
    }
    
    while (qq--) {
        int t;
        cin >> t;
        if (t == 1) {
            int lx, rx, out = 0;
            cin >> lx >> rx;
            lx--, rx--;
            int lxb = (lx + blk - 1) / blk, rxb = rx / blk;
            if (lxb >= rxb) {
                for (int i = lx; i <= rx; i++) {
                    if (sq[l[i]] == -1) out += a[i];
                }
            }
            
            else {
                for (int i = lx; i < blk * lxb; i++) {
                    if (sq[l[i]] == -1) out += a[i];
                }
                
                for (int i = lxb; i < rxb; i++) {
                    out += sum[i];
                }
                
                for (int i = blk * rxb; i <= rx; i++) {
                    if (sq[l[i]] == -1) out += a[i];
                }
            }
            
            // cout << out << "\n";
            for (int i = 0; i < cntblk; i++) {
                if (id[i] == -1) break;
                int lxx = nextleft[i][lx], rxx = nextright[i][rx];
                // cout << i << " " << lxx << " " << rxx << "\n";
                if (lxx == -1 || rxx == -1) continue;
                lxx = (lxx + rot[i]) % cnt[id[i]], rxx = (rxx + rot[i]) % cnt[id[i]];
                out += pref[id[i]][rxx] - (lxx == 0 ? 0 : pref[id[i]][lxx - 1]);
                if (lxx > rxx) out += pref[id[i]][cnt[id[i]] - 1];
            }
            
            cout << out << "\n";
        }
        
        else {
            int x;
            cin >> x;
            x--;
            if (sq[x] == -1) {
                int sz = vals[x].size();
                for (int i = 0; i < sz; i++) {
                    sum[pos[x][i] / blk] -= vals[x][i];
                }
                
                rotate(vals[x].begin(), vals[x].begin() + sz - 1, vals[x].end());
                for (int i = 0; i < sz; i++) {
                    a[pos[x][i]] = vals[x][i];
                    sum[pos[x][i] / blk] += vals[x][i];
                }
            }
            
            else {
                rot[sq[x]]--;
                if (rot[sq[x]] < 0) rot[sq[x]] += cnt[x];
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    solve();
}