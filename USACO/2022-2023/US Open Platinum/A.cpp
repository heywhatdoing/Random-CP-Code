#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 10;
ll t[N * 4][6][8], ans[N * 4];
int n, qq;
string s;
void merge(int v, int l, int r) {
    int lv = v * 2, rv = v * 2 + 1, mid = (l + r) / 2;
    int sz1 = mid - l + 1, sz2 = r - mid;
    for (int i = 0; i < 6; i++) {
        int nxt1 = t[lv][i][6];
        int nxt2 = t[rv][nxt1][6];
        t[v][i][6] = nxt2;
        int nxt3 = t[rv][i][7];
        int nxt4 = t[lv][nxt3][7];
        t[v][i][7] = nxt4;
        cout << v << " " << i << " " << nxt3 << " " << nxt4 << " " << l << " " << r << "\n";
        t[v][i][0] = t[rv][i][0] + t[rv][nxt3][0];
        t[v][i][1] = t[lv][i][1] + t[lv][nxt1][1];
        t[v][i][4] = t[rv][i][4] + t[rv][nxt3][4];
        t[v][i][5] = t[lv][i][5] + t[lv][nxt1][5];
        t[v][i][2] = t[rv][i][2] + t[rv][nxt3][2] + t[rv][i][4] * sz2;
        t[v][i][3] = t[lv][i][3] + t[lv][nxt1][3] + t[lv][i][5] * sz1;
        ans[v] += t[lv][i][2] * t[rv][i][3];
    }
    
    ans[v] += ans[lv] + ans[rv];
}

void updatenode(int v, char c) {
    if (c == 'b') {
        t[v][0][0] = 1, t[v][0][1] = 1;
    }
    
    if (c == 'e') {
        t[v][5][4] = 1, t[v][5][5] = 1;
    }
    
    for (int i = 0; i < 6; i++) {
        if ((c == 'b' && i == 0) || (c == 'e' && (i == 1 || i == 5)) || 
            (c == 's' && (i == 2 || i == 3)) || (c == 'i' && i == 4)) {
            t[v][i][6] = i + 1;
            if (t[v][i][6] == 6) t[v][i][6] = 0;
        }
        
        else {
            t[v][i][6] = i;
        }
        
        if ((c == 'b' && i == 0) || (c == 'e' && (i == 1 || i == 5)) || 
            (c == 's' && (i == 2 || i == 3)) || (c == 'i' && i == 4)) {
            t[v][(i + 1) % 6][7] = i;
        }
        
        else {
            t[v][i][7] = i;
        }
    }
}

void init(int v = 1, int l = 0, int r = n - 1) {
    if (l == r) {
        updatenode(v, s[l]);
        return;
    }
    
    int mid = (l + r) / 2;
    init(v * 2, l, mid);
    init(v * 2 + 1, mid + 1, r);
    merge(v, l, r);
}

void update(int p, int v = 1, int l = 0, int r = n - 1) {
    if (l == r) {
        updatenode(v, s[l]);
        return;
    }
    
    int mid = (l + r) / 2;
    if (p <= mid) update(p, v * 2, l, mid);
    else update(p, v * 2 + 1, mid + 1, r);
    merge(v, l, r);
}

void solve() {
    cin >> s >> qq;
    n = s.size();
    init();
    cout << ans[1] << "\n";
    for (int i = 0; i < qq; i++) {
        int p;
        char c;
        cin >> p >> c;
        p--;
        s[p] = c;
        update(p);
        cout << ans[1] << "\n";
    }
}

int main() {
    solve();
}