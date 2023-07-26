#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int N = 200005;
const int inf = 1e9 + 5;
int n, m, r, c;
void solve() {
    cin >> n >> m >> r >> c;
    
    if ((r == 0 && c < m) || (c == 0 && r < n)) {
        vector<vector<char>> a(n, vector<char>(m, 'f'));
        if (r == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < c; j++) {
                    a[i][j] = 'e';
                }
            }
        }
        
        else {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < m; j++) {
                    a[i][j] = 'e';
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == 'e') continue;
                if (i < n - 1 && j < m - 1) a[i][j] = 'a';
                else if (i == n - 1 && j < m - 1)  a[i][j] = 'b';
                else if (i < n - 1 && j == m - 1)  a[i][j] = 'c';
                else a[i][j] = 'd';
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j];
            }
            
            cout << "\n";
        }
    }
    
    else if ((r < n && c < m) || (r == n && c == m)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i < r || j < c) {
                    cout << "a";
                }
                
                else {
                    cout << "b";
                }
            }
            
            cout << "\n";
        }
    }
    
    else {
        bool flip = false;
        if (r < n && c == m) {
            swap(n, m);
            swap(r, c);
            flip = true;
        }
        
        if (m % 2 == 0 && c % 2 == 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        
        vector<vector<char>> a(n, vector<char>(m, 'd'));
        int amt = c / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < amt; j++) {
                a[i][j] = 'a';
            }
            
            for (int j = m - 1; j > m - 1 - amt; j--) {
                a[i][j] = 'a';
            }
            
            for (int j = amt; j <= m - 1 - amt; j++) {
                if (i == 0) a[i][j] = 'b';
                else a[i][j] = 'c';
            }
        }
        
        if (c % 2 == 1) {
            int j = m / 2;
            for (int i = 0; i < n; i++) {
                a[i][j] = 'a';
            }
        }
        
        if (!flip) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << a[i][j];
                }
                
                cout << "\n";
            }
        }
        
        else {
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++) {
                    cout << a[i][j];
                }
                
                cout << "\n";
            }
        }
    }
}

int main() {
    solve();
}