#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    int x, y;
    x = sx, y = sy;
    while(y < ty) {
        cout << "U";
        y++;
    }
    while(x < tx) {
        cout << "R";
        x++;
    }
    cout << "U";
    y++;
    while(x >= sx) {
        cout << "L";
        x--;
    }
    while(y > sy) {
        cout << "D";
        y--;
    }
    cout << "R";
    x++;
    while(x < tx) {
        cout << "R";
        x++;
    } 
    while(y < ty) {
        cout << "U";
        y++;
    }
    cout << "R";
    x++;
    while(y >= sy) {
        cout << "D";
        y--;
    }
    while(x > sx) {
        cout << "L";
        x--;
    }
    cout << "U";
    y++;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
