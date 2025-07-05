#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


vector<ll> powk;
ll dis(ll x, ll y) {
    if(x <= 3 && y <= 3) {
        if(x == 1) {
            return y - 1;
        } else if(x == 2) {
            return 6 - y;
        } else {
            return 5 + y;
        }
    }
    ll ans = 0;
    int i = 1;
    while(x > powk[i]) i++;
    while(y > powk[i]) i++;
    ll pre = powk[i - 1], tot = pre * pre;
    int flag1 = (x + pre - 1) / pre, flag2 = (y + pre - 1) / pre;
    ll nx = 1 + (x - 1) % pre, ny = 1 + (y - 1) % pre;
    if(flag1 == 1) {
        if(flag2 == 2) {
            ans = tot + dis(pre - nx + 1, ny);
        } else {
            ans = 2 * tot + dis(nx, ny);
        }
    } else if(flag1 == 2) {
        if(flag2 == 3) {
            ans = 3 * tot + dis(nx, pre - ny + 1);
        } else if(flag2 == 2) {
            ans = 4 * tot + dis(pre - nx + 1, pre - ny + 1);
        } else {
            ans = 5 * tot + dis(nx, pre - ny + 1);
        }
    } else {
        if(flag2 == 1) {
            ans = 6 * tot + dis(nx, ny);
        } else if(flag2 == 2){
            ans = 7 * tot + dis(pre - nx + 1, ny); 
        } else {
            ans = 8 * tot + dis(nx, ny);
        }
    }
    return ans;
} 
ll dfs(int n) {
    if(n == 1) return 24;
    ll ans = 9 * dfs(n - 1);
    ll x1 = powk[n] / 3, x2 = powk[n] - x1;
    ll y1 = x1, y2 = x2;
    for(ll i = 1; i <= powk[n]; i++) {
        ans += abs(dis(x1 + 1, i) - dis(x1, i));
        ans += abs(dis(x2 + 1, i) - dis(x2, i));
        ans += abs(dis(i, y1 + 1) - dis(i, y1));
        ans += abs(dis(i, y2 + 1) - dis(i, y2));
    }
    return ans;
}
void solve() { 
    powk.resize(13);
    powk[0] = 1;
    for(int i = 1; i <= 12; i++) powk[i] = powk[i - 1] * 3;
    ll ans = dfs(12);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
