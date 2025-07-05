#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int N = 8;
int x;
vector<int> a(N + 1);
vector<vector<ll>> memo(N + 1, vector<ll>(N + 1, -1)); 
ll dfs(int pos, int cnt, bool head, bool lim) {
    if(pos == 0) return cnt;
    if(memo[pos][cnt] != -1 && !head && !lim) return memo[pos][cnt];
    int up = (lim ? a[pos] : 9);
    ll res = 0;
    for(int i = 0; i <= up; i++) {
        if(head && i == 0) res += dfs(pos - 1, cnt, true, lim && i == up);
        else if(i == x) res += dfs(pos - 1, cnt + 1, false, lim && i == up);
        else res += dfs(pos - 1, cnt, false, lim && i == up); 
    }
    if(!head && !lim) memo[pos][cnt] = res;
    return res;
}
void solve() { 
    int n;
    cin >> n >> x;
    int cnt = 0;
    while(n) {
        a[++cnt] = n % 10;
        n /= 10;
    }
    ll ans = dfs(cnt, 0, true, true);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
