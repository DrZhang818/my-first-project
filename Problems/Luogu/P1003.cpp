#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct info {
    int x1, x2, y1, y2;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        a[i].x2 += a[i].x1;
        a[i].y2 += a[i].y1;
    }
    int x, y;
    cin >> x >> y;
    int ans = -1;
    for(int i = n; i >= 1; i--) {
        if(a[i].x1 <= x && a[i].y1 <= y && a[i].x2 >= x && a[i].y2 >= y) {
            ans = i;
            break;
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
    
