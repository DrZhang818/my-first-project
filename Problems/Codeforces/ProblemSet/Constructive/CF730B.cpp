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
    if(n == 1) {
        cout << "! " << 1 << " " << 1 << endl;
        return;
    }
    vector<int> mn, mx;
    for(int i = 1; i < n; i += 2) {
        cout << "? " << i << " " << i + 1 << endl;
        char c;
        cin >> c;
        if(c == '>' || c == '=') {
            mx.push_back(i);
            mn.push_back(i + 1);
        } else {
            mn.push_back(i);
            mx.push_back(i + 1);
        }
    }
    if(n & 1) {
        cout << "? " << n - 1 << " " << n << endl;
        char c;
        cin >> c;
        if(c == '>') {
            mn.push_back(n);
        } else {
            mx.push_back(n);
        }
    }
    int x = mn[0], y = mx[0];
    for(int i = 1; i < mn.size(); i++) {
        cout << "? " << x << " " << mn[i] << endl;
        char c;
        cin >> c;
        if(c == '>') {
            x = mn[i];
        }
    }
    for(int i = 1; i < mx.size(); i++) {
        cout << "? " << y << " " << mx[i] << endl;
        char c;
        cin >> c;
        if(c == '<') {
            y = mx[i];
        }
    }
    cout << "! " << x << " " << y << endl;
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
