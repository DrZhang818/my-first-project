#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n;
vector<int> tr;
void add(int o, int d) { for(; o <= n; o += o & -o) tr[o] += d; }
int query(int o) {
    int res = 0;
    for(; o > 0; o -= o & -o) res += tr[o];
    return res;
}

void solve() { 
    string s;
    cin >> s;
    n = s.size();
    tr.resize(n + 2);
    s = "#" + s;
    vector<int> c(26);
    for(int i = 1; i <= n; i++) c[s[i] - 'a']++;
    int odd = 0;
    char tar;
    for(int i = 0; i < 26; i++) if(c[i] % 2 == 1) odd++, tar = i + 'a';
    if(odd > 1) {
        cout << -1 << "\n";
        return;
    }
    int cnt = 0;
    vector<deque<int>> dq(26);
    for(int i = 1; i <= n; i++) {
        dq[s[i] - 'a'].push_back(i);
    }
    vector<bool> vis(n + 1);
    int i = 1, cur = 1, flag = 0;
    ll ans = 0;
    for(; i <= n / 2; i++) {
        while(vis[cur]) cur++;
        int it = dq[s[cur] - 'a'].back();
        if(it == cur) {
            flag = 1;
            vis[cur] = true;
            i--;
            continue;
        }
        int en = it - query(it);
        // cerr << i << " " << cur << " " << en << "\n";
        ans += n - i + 1 - en + flag;
        vis[it] = vis[cur] = true;
        add(it, 1);
        dq[s[cur] - 'a'].pop_back();
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
