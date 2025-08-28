#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y;
};
void solve() {
    vector<info> a(4);
    for(int i = 1; i <= 3; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for(int i = 1; i <= 3; i++) {
        for(int j = i + 1; j <= 3; j++) {
            int x1 = a[i].x - a[i ^ j].x;
            int y1 = a[i].y - a[i ^ j].y;
            int x2 = a[j].x - a[i ^ j].x;
            int y2 = a[j].y - a[i ^ j].y;
            if(x1 * x2 + y1 * y2 == 0) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
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
