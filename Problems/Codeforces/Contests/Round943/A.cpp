#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int G[1001][1001];
void solve() {
    int x;
    cin >> x;
    int cur = 0, y = 0;
    for(int i = 1; i < x; i++) {
        if(G[x][i] + i > cur) {
            cur = G[x][i] + i;
            y = i;
        }
    }
    cout << y << "\n";
}

int main()
{
    ios::sync_with_stdio(false);    
    cin.tie(0);

    for(int i = 1; i <= 1000; i++) {
        G[i][i] = i;
        for(int j = 1; j < i; j++) {
            G[i][j] = G[j][i] = G[i - j][j];
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
