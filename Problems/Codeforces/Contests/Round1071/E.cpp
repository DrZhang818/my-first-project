#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    s = "#" + s;
    vector<int> p(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        sum += p[i];
    }
    if(x + y < sum) {
        cout << "NO\n";
        return;
    }
    ll suma = 0, sumb = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') {
            suma += p[i] / 2 + 1;
        } else {
            sumb += p[i] / 2 + 1;
        }
    }
    if(count(s.begin() + 1, s.end(), '0') == n) {
        if(suma > x || y > x - n) {
            cout << "NO\n";
            return;
        }
        cout << "YES\n";
    } else if(count(s.begin() + 1, s.end(), '1') == n) {
        if(sumb > y || x > y - n) {
            cout << "NO\n";
            return;
        }
        cout << "YES\n";
    } else {
        if(suma > x || sumb > y) {
            cout << "NO\n";
            return;
        }
        ll need = 0;
        for(int i = 1; i <= n; i++) {
            need += p[i] - ((p[i] / 2) + 1);
        }
        ll rem = x - suma + y - sumb;
        if(rem >= need) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
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
