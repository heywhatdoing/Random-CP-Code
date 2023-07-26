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

const int mod=1000000007;
const int N=100005;
const int inf=1e9;
const double eps=1e-11;
int n, m, k;
vector<int> out, s;
vector<bool> vis1(N), vis2(N), vis3(N);
vector<vector<array<int, 3>>> adj(N);
int cntedges, x, edge;
void count(int u) {
    s.push_back(u);
    vis1[u]=true;
    for (auto [v, e, dir]:adj[u]) {
        if (!vis1[v]) {
            count(v);
        }
        
        cntedges++;
    }
}

void findcycle(int u, int parent) {
    vis3[u]=true;
    for (auto [v, e, dir]:adj[u]) {
        if (vis3[v]==true && v!=parent) {
            x=(dir==0 ? v : u);
            edge=e;
        }
        
        if (!vis3[v]) {
            findcycle(v, u);
        }
    }
}

void removenodes(int u) {
    vis2[u]=true;
    for (auto [v, e, dir]:adj[u]) {
        if (!vis2[v]) {
            out.push_back(e);
            removenodes(v);
        }
    }
}

void solve() {
    cin>>m>>n;
    vector<int> indeg(N);
    vector<pi> edges(N);
    for (int i=0; i<m; i++) {
        int u, v;
        cin>>u>>v;
        u--, v--;
        edges[i]={u, v};
        indeg[u]++;
        adj[v].push_back({u, i, 0});
        adj[u].push_back({v, i, 1});
    }
    
    int hungry=0;
    for (int i=0; i<n; i++) {
        if (vis1[i]) continue;
        cntedges=0;
        s.clear();
        count(i);
        int cntnodes=s.size();
        cntedges/=2;
        hungry+=max(0, cntedges-cntnodes);
        if (cntnodes>cntedges) {
            for (int u:s) {
                if (indeg[u]==0) {
                    vis2[u]=true;
                    for (auto [v, e, dir]:adj[u]) {
                        out.push_back(e);
                        removenodes(v);
                    }
                    
                    break;
                }
            }
        }
        
        else {
            findcycle(i, -1);
            // dbgm(x, edge);
            vis2[x]=true;
            out.push_back(edge);
            for (auto [v, e, dir]:adj[x]) {
                if (e!=edge) {
                    out.push_back(e);
                    removenodes(v);
                }
            }
        }
        
        // dbg(i);
    }
    
    vector<bool> used(N);
    for (int e:out) {
        used[e]=true;
    }
    
    for (int i=0; i<m; i++) {
        if (!used[i]) out.push_back(i);
    }
    
    cout<<hungry<<"\n";
    for (int e:out) {
        cout<<e+1<<"\n";
    }
    
    // int test=0;
    // vector<bool> cereal(N, true);
    // for (int i=0; i<m; i++) {
    //     auto [u, v]=edges[out[i]];
    //     if (cereal[u]) cereal[u]=false;
    //     else if (cereal[v]) cereal[v]=false;
    //     else test++;
    // }
    
    // if (test!=hungry) {
    //     cout<<"Test: "<<test<<"\n";
    //     cout<<"Hungry: "<<hungry<<"\n";
    // }
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