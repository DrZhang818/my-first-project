#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ll MOD = ll(1E18) + 9;
const ll P = 13131;

ll get(vector<vector<char>> &a) {
    ll H = 0;
    for(int i = 1; i < a.size(); i++) {
        for(int j = 1; j < a[1].size(); j++) {
            H = (H * P + a[i][j]) % MOD; 
        }
    }
    return H;
}
vector<PII> dir{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<char>(m + 1));
    int x, y; 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'T') {
                x = i;
                y = j;
            }
        }
    }
    set<ll> st;
    using T = vector<vector<char>>;
    queue<T> q;
    q.push(a);
    int ans = 0;
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            T cur = q.front(); q.pop();
            for(int s = 0; s < 4; s++) {
                T nxt(n + 1, vector<char>(m + 1, '.'));
                nxt[x][y] = 'T';
                bool ok = true, has = false;
                for(int i = 1; i <= n && ok; i++) {
                    for(int j = 1; j <= m; j++) {
                        if(cur[i][j] == '#') {
                            has = true;
                            int ni = i + dir[s].first;
                            int nj = j + dir[s].second;
                            if(ni < 1 || ni > n || nj < 1 || nj > m) {
                                continue;
                              }
                            if(nxt[ni][nj] == 'T') {
                                ok = false;
                                break;
                            }
                            nxt[ni][nj] = '#';
                        }
                    }
                }
                if(ok && !has) {
                    cout << ans << "\n";
                    return;                    
                }
                if(!ok) continue;
                ll H = get(nxt);
                if(st.contains(H)) continue;
                q.push(nxt);
                st.insert(H);
            }
        }
        ans++;
    }
    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
