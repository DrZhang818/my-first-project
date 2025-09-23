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
    string s;
    cin >> s;
    s = "#" + s;
    vector<int> a(n + 1);
    int las = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '1') {
            a[i] = i;
            if(i - las == 2) {
                cout << "NO\n";
                return;
            }
            for(int j = las + 1, c = i - 1; j < i; j++, c--) {
                a[j] = c;
            }
            las = i;
        } else if(i == n) {
            if(i - las == 1) {
                cout << "NO\n";
                return;
            }
            for(int j = las + 1, c = i; j <= i; j++, c--) {
                a[j] = c;
            }
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
