#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    vector<vector<int>> a(6, vector<int>(6));
    ll ans = 0;
    auto dfs = [&](auto &&dfs, int x, int y, int c0, int c1) -> void {
        if(x == 6) {
            bool ok1 = false, ok2 = false, ok3 = true;
            for(int i = 1; i <= 5; i++) {
                if(a[i][i] != a[1][1]) ok1 = true;
            }
            for(int i = 1; i <= 5; i++) {
                if(a[i][6 - i] != a[1][5]) ok2 = true;
            }
            for(int i = 1; i <= 5; i++) {
                int cnt = 0;
                for(int j = 1; j <= 5; j++) {
                    if(a[i][j] == a[i][1]) {
                        cnt++;
                    }
                }
                if(cnt == 5) {
                    ok3 = false;
                    break;
                }
            }
            if(ok3) {
                for(int j = 1; j <= 5; j++) {
                    int cnt = 0;
                    for(int i = 1; i <= 5; i++) {
                        if(a[i][j] == a[1][j]) {
                            cnt++;
                        }
                    }
                    if(cnt == 5) {
                        ok3 = false;
                        break;
                    }
                }
            }
            if(ok1 && ok2 && ok3 && (c0 == 12 && c1 == 13)) {
                ans += 1;
            }
            return;
        }
        if(c0 > 13 || c1 > 13) return;
        for(int i = 0; i <= 1; i++) {
            a[x][y] = i;
            if(y == 5) dfs(dfs, x + 1, 1, c0 + (i == 0), c1 + (i == 1));
            else dfs(dfs, x, y + 1, c0 + (i == 0), c1 + (i == 1));
        }
    };
    dfs(dfs, 1, 1, 0, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
