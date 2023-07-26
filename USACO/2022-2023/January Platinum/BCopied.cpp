#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
vector<ll> rates;
ll dist[19][19];
ll inf = 1e9+1;
ll inf2 = 2e18;
int N, Q;
ll maskDeriv[1<<18];
ll dp[18][1<<18];
vector<pair<ll, ll> > hull[18];
vector<ll> hull_pt;

ll go(int now, int rem){
    // computing optimal add_J that ends at now, and visits everything remaining in rem
    if(rem == 0){
        return 0LL;
    }
    if(dp[now][rem] <= 0LL){
        return dp[now][rem];
    }
    ll ret = -inf2;
    for(int i = 0; i<N; i++){
        if((rem&(1<<i))!=0){
            ret = max(ret,go(i,rem-(1<<i)) - maskDeriv[rem] * dist[i][now]);
        }
    }
    dp[now][rem] = ret;
    return ret;
}
 
ll overcome(pair<ll, ll> a, pair<ll, ll> b){
    // when does line "a" with slope a.f and add a.s, take over line "b" with slope b.f and add b.s
    assert((a.f >= b.f) && (a.s <= b.s));
    ll slopeDif = a.f - b.f;
    ll addDif = b.s - a.s;
    ll addOne = ((addOne%slopeDif)==0)?1:0;
    return addDif/slopeDif + addOne;
}

void ins(int loc, ll slope, ll add){
    // insert a line to the hull
    // corresponds to a journey ending at loc
    auto cur = make_pair(slope,add);
    if(hull[loc].size()>0 && (hull[loc].back().f == slope) && hull[loc].back().s >= add){
        return;
    }
    while(true){
        int sz = (int)(hull[loc].size());
        if(sz==0){
            break;
        }
        auto bef = hull[loc][sz-1];
        // if the previous line has worse slope and add than the new line, delete it
        if(bef.s < add){
            hull[loc].pop_back();
            continue;
        }
        if(sz == 1){
            break;
        }
        auto grandBef = hull[loc][sz-2];
        // if the new line overcomes the second-newest before the second-newest overcomes the third-newest
        // then the second-newest is never on the hull, so we delete it
        if(overcome(bef,grandBef) >= overcome(cur,bef)){
            hull[loc].pop_back();
            continue;
        }
        break;
    }
    hull[loc].push_back(cur);
}
 
ll query(int loc, ll t){
    // query the hull for ending location loc at time t
    int sz = (int)(hull[loc].size());
    while(hull_pt[loc]+1<sz){
        auto it = hull[loc].begin();
        auto val1 = hull[loc][hull_pt[loc]];
        it++;
        auto val2 = hull[loc][hull_pt[loc]+1];
        if(overcome(val2,val1) > t){
            break;
        }
        hull_pt[loc]++;
    }
    auto val = (hull[loc][hull_pt[loc]]);
    return t * val.f + val.s;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> N >> m;
    hull_pt.resize(N);
    for(int i = 0; i<N; i++){
        ll x;
        cin >> x;
        rates.push_back(x);
    }
    for(int i = 0; i<=N; i++){
        for(int j = 0; j<=N; j++){
            dist[i][j] = inf;
        }
    }
    for(int i = 0; i<m; i++){
        int a, b;
        ll t;
        cin >> a >> b >> t;
        a--;
        b--;
        dist[a][b] = t;
    }
    // compute shortest paths
    for(int k = 0; k<N; k++){
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }
    // compute the total rate of all masks
    maskDeriv[0] = 0L;
    for(int mask = 1; mask<(1<<N); mask++){
        for(int i = 0; i<N; i++){
            if((mask&(1<<i))!=0){
                maskDeriv[mask] = maskDeriv[mask - (1<<i)] + rates[i];
                break;
            }
        }
    }
    for(int i = 0; i<(1<<N); i++){
        for(int j = 0; j<N; j++){
            dp[j][i] = 1LL;
        }
    }
    int all = (1<<N) - 1;
    vector<pair<ll, pair<ll, int> > > lines;
    for(int mask = 0; mask<(1<<N); mask++){
        for(int j = 0; j<N; j++){
            if((mask&(1<<j))==0){
                // considers the line for a journey ending at location j
                // maskDeriv[mask|(1<<j)] is slope
                // go(j,mask) is add
                lines.push_back(make_pair(maskDeriv[mask|(1<<j)],make_pair(go(j,mask),j)));
            }
            
        }
    }
    sort(lines.begin(),lines.end());
    // insert lines into hull in order of slope
    for(auto x: lines){
        ins(x.s.s, x.f,x.s.f);
    }
    cin >> Q;
    vector<ll> ans(Q);
    vector<pair<ll, pair<int, int> > > queries;
    for(int i = 0; i<Q; i++){
        ll s;
        int e;
        cin >> s >> e;
        e--;
        // consider query i for ending at e after s seconds
        queries.push_back(make_pair(s,make_pair(e,i)));
    }
    // consider queries in order of time
    sort(queries.begin(),queries.end());
    for(int i = 0; i<Q; i++){
        ll t = queries[i].f;
        int loc = queries[i].s.f;
        int id = queries[i].s.s;
        // query the relevant hull at the relevant time
        ans[id] = query(loc,t);
    }
    for(int i = 0; i<Q; i++){
        cout << ans[i] << "\n";
    }
}