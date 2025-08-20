#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

PII dir[] = {{-1,-1},{-1,0},{0,-1},{1,0},{1,1},{1,-1},{0,1},{-1,1}};
void solve() {
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    string ans;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int p = 0; p < 8; p++) {
                string s;
                int x = i, y = j;
                for(int k = 0; k < n; k++) {
                    s += a[x][y];
                    x = (x + dir[p].first + n) % n;
                    y = (y + dir[p].second + n) % n;
                }
                ans = max(ans, s);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
