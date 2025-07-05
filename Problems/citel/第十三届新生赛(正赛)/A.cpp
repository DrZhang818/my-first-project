#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    一水签到题
    模拟
    题意: 给定11组x和y, 求出每组x + 20y的总和
    即ans = sigma(xi + 20yi)
*/
void solve(){
    int ans = 0;
    for(int i = 0; i < 11; i++){
        int x, y;
        cin >> x >> y;
        ans += x + 20 * y;
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