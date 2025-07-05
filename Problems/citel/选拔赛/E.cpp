#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &r : grid){
        for(auto &c : r){
            cin >> c;
        }
    }
    ll ans = 0;
    for(int i = 1; i < n - 1; i++){
        for(int j = 1; j < m - 1; j++){
            int num = grid[i][j];
            bool ok = true;
            for(int k = i - 1; k <= i + 1; k++){
                for(int t = j - 1; t <= j + 1; t++){
                    if(k == i && t == j) continue;
                    if(num >= grid[k][t]){
                        ok = false;
                        break;
                    }
                }
            }
            if(ok){
                ans++;
            }
        }
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