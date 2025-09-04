#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n + 1), pos;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            pos.push_back(i + 1);
        }
    }
    int num = 0;
    for(int i = 0, cnt = 0; i < pos.size(); i++) {
        if(i && pos[i] == pos[i - 1] + 1) {
            cnt++;
        } else {
            cnt = 1;
        }
        if(cnt >= k) {
            cout << "NO\n";
            return;
        }
        a[pos[i]] = ++num;
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        if(!a[i]) {
            a[i] = ++num;
        }
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
