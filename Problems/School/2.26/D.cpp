#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        int u = i;
        for(int j = 1; j <= n - 1; j++) {
            int v;
            cin >> v;
            if(grid[u][v]) {
                cout << -1 << "\n";
                return;
            }
            grid[u][v] = 1;
            u = v;
        }
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
