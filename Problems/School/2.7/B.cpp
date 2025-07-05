#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    vector<bool> row(n, false), col(m, false);
    for(int i = 0; i < n; i++) {
        char c = '.';
        bool ok = false;
        for(int j = 0; j < m; j++) {
            if(grid[i][j] != c) {
                ok = true;
                break;
            }
        }
        row[i] = ok;
    }
    for(int j = 0; j < m; j++) {
        char c = '.';
        bool ok = false;
        for(int i = 0; i < n; i++) {
            if(grid[i][j] != c) {
                ok = true;
                break;
            }
        }
        col[j] = ok;
    }
    for(int i = 0; i < n; i++) {
        if(!row[i]) continue;
        for(int j = 0; j < m; j++) {
            if(col[j]) {
                cout << grid[i][j];
            }
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

