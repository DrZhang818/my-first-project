#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    int sx, sy, ex, ey;
    int x = 0, y = 0;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        x += a;
        y += b;
        if(i == 0){
            sx = x;
            sy = y;
        }
        if(i == n - 1){
            ex = x + m;
            ey = y + m;
        }
    }
    cout << 2 * (ex - sx) + 2 * (ey - sy) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}