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

#define double128 __float128
using u128=__uint128_t;
using i128=__int128;
const int mod=1000000007;
const int N=1005;
const int LOG=20;
const int inf=1e9;
const double eps=1e-11;
string s;
int n, m, k, qq;
double128 fact[N], p[N], pref[N], suf[N], C[N][N];
double128 binaryexp(double128 b, int e) {
    double128 res=1, cur=b;
    while (e) {
        if (e&1) res*=cur;
        cur*=cur;
        e>>=1;
    }    
    
    return res;
}

void solve() {
    cin>>n>>k;
    n--;
    cout<<setprecision(20);
    C[0][0]=1;
    for (int i=1; i<N; i++) {
        for (int j=0; j<=i; j++) {
            C[i][j]=(C[i-1][j]+(j==0 ? 0 : C[i-1][j-1]))/2;
        }
    }
    
    for (int i=0; i<=n; i++) {
        p[i]=C[n][i];
        pref[i]=p[i]+(i==0 ? 0 : pref[i-1]);
    }
    
    for (int i=n; i>=0; i--) {
        suf[i]=p[i]*i+suf[i+1];
    }
    
    int left=k-1;
    double128 out=0;
    for (int i=0; i<=n; i++) {
        out+=i*p[i];
    }
    
    // dbg(pref);
    // dbg(suf);
    for (int i=0; i<=n; i++) {
        if (left==0) break;
        if (i<out) continue;
        double128 cur=pref[i-1]*out+suf[i], diff=i-out, ratio=pref[i-1];
        double128 diff2=cur-out;
        int l=1, r=left, res=-1;
        while (l<=r) {
            int mid=(l+r)/2;
            //geometric series calc
            double128 test=1/(1.0-ratio)*diff2*(1-binaryexp(ratio, mid));
            // dbgm(test, mid, binaryexp(ratio, mid));
            if (test+out>=i) {
                r=mid-1, res=mid;
            }
            
            else {
                l=mid+1;
            }
        }
        
        // dbgm(1, cur, diff, diff2, ratio, out, left);
        if (res==-1) {
            out+=1/(1.0-ratio)*diff2*(1-binaryexp(ratio, left));
            break;
        }
        
        else {
            out+=1/(1.0-ratio)*diff2*(1-binaryexp(ratio, res));
            left-=res;
        }
    }
    
    // dbg(p);
    // cout<<out<<"\n";
    cout<<(long double)(out+1)<<"\n";
	
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