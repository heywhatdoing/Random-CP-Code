#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int N = 400005;
const int LOG = 20;
const int inf = 1e9 + 5;
int n, qq;
int a[N], rightmost[N], up[N][LOG];
int main() {
    cin >> n >> qq;
    queue<int> q;
    vector<int> special;
    vector<pi> ranges;
    for (int i = 0; i < N; i++) {
        a[i] = -1, rightmost[i] = -1;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = -1;
        }    
    }
    
    for (int i = 0; i < 2 * n; i++) {
        char c;
        cin >> c;
        if (c == 'L') {
            q.push(i);
        }
        
        else {
            int l = q.front();
            q.pop();
            a[l] = i;
            ranges.push_back({l, i});
        }
    }
    
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '1') special.push_back(i);
    }
    
    int mx = 0, cur = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (a[i] == -1) continue;
        while (cur < a[i]) {
            if (a[cur] != -1) mx = cur;
            cur++;
        }
        
        rightmost[i] = mx;
        up[i][0] = mx;
    }
    
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n * 2; i++) {
            if (up[i][j - 1] == -1) up[i][j] = -1;
            else {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    
    auto query = [&](int u, int v) -> int {
        if (u == v) return 0;
        int res = inf, cur = 0;
        for (int j = LOG - 1; j >= 0; j--) {
            int next = up[u][j];
            if (next == -1) continue;
            if (next >= v) {
                res = cur + (1 << j);
            }
            
            else {
                u = up[u][j], cur += 1 << j;
            }
        }
        
        return res;
    };
    
    while (qq--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        x = ranges[x].first, y = ranges[y].first;
        int dis = query(x, y), cnt = 0;
        cout << dis << " ";
        for (int s : special) {
            int z = ranges[s].first;
            if (z >= x && z <= y && query(x, z) + query(z, y) == dis) cnt++;
        }
        
        cout << cnt << "\n";
    }
}