#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int MX = 1e6;
constexpr ll inf = 1e13;
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<PII>> from(n + 1), to(n + 1);
    for(int i = 0; i < m; i++){
        int d, f, t, c;
        cin >> d >> f >> t >> c;
        if(f == 0) to[t].emplace_back(d, c);
        else from[f].emplace_back(d, c);
    }
    vector<ll> pre(MX + 2), suf(MX + 2);
    ll v;
    for(int i = 1; i <= n; i++){
        sort(from[i].begin(), from[i].end());
        sort(to[i].begin(), to[i].end());
        int fk = from[i].size();
        int tk = to[i].size();
        if(fk == 0 || tk == 0){
            cout << -1 << "\n";
            return ;
        }
        v = inf;
        pre[0] += inf;
        pre[from[i][0].first] -= inf;
        for(int j = 0; j < fk - 1; j++){
            v = min(v, (ll)from[i][j].second);
            pre[from[i][j].first] += v;
            pre[from[i][j + 1].first] -= v;
        }   
        v = min(v, (ll)from[i][fk - 1].second);
        pre[from[i][fk - 1].first] += v;
        pre[MX + 1] -= v;

        v = inf;
        suf[to[i][tk - 1].first + 1] += inf;
        suf[MX + 1] -= inf;
        for(int j = tk - 2; j >= 0; j--){
            v = min(v, (ll)to[i][j + 1].second);
            suf[to[i][j].first + 1] += v;
            suf[to[i][j + 1].first + 1] -= v;
        }
        v = min(v, (ll)to[i][0].second);
        suf[0] += v;
        suf[to[i][0].first + 1] -= v;
    }
    ll ans = inf;
    for(int i = 0; i <= MX; i++){
        pre[i + 1] += pre[i];
        suf[i + 1] += suf[i];
    }
    for(int i = 0; i <= MX + 1; i++){
        if(i + k + 1 <= MX) ans = min(ans, pre[i] + suf[i + k + 1]);
        else break;
    }
    if(ans < inf) cout << ans << "\n";
    else cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

