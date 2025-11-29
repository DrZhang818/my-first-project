#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector a(n + 1, vector<char>(n + 1));
    vector<PII> b;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            a[i][j] = c;
            if(c == '#') {
                b.emplace_back(i, j);
            }
        }
    }
    for(int i = 0; i < b.size(); i++) {
        for(int j = i + 1; j < b.size(); j++) {
            auto [x1, y1] = b[i];
            auto [x2, y2] = b[j];
            if(abs(abs(x1 - x2) - abs(y1 - y2)) >= 2) {
                cout << "NO\n";
                return;
            }
        }
    }
    int cnt = 0;
    bool found = false;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i][j] == '#') {
                cnt++;
                if(i + 1 > n || j + 1 > n) continue;
                if(a[i + 1][j] == '#' && a[i][j + 1] == '#' && a[i + 1][j + 1] == '#') {
                    found = true;
                }
            }
        }
    }
    if(found) {
        if(cnt != 4) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
        return;
    }
    if(b.size() == 0) {
        cout << "YES\n";
        return;
    }
    sort(b.begin(), b.end(),
        [&](auto x, auto y) {
            if(x.first != y.first) {
                return x.first < y.first;
            }
            return x.second > y.second;
        });
    bool ok = true;
    for(int i = 1; i < b.size(); i++) {
        if(b[i].second > b[i - 1].second) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << "YES\n";
        return;
    }
    ok = true;
    sort(b.begin(), b.end(),
        [&](auto x, auto y) {
            if(x.first != y.first) {
                return x.first < y.first;
            }
            return x.second < y.second;
        });
    for(int i = 1; i < b.size(); i++) {
        if(b[i].second < b[i - 1].second) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
