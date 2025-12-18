#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> val;
    int _xor = 0;
    for(int i = 1, j = 1; i <= 2 * n; i = j) {
        while(j <= 2 * n && a[j] == a[i]) {
            j++;
        }
        int c = j - i;
        if(c & 1) {
            val.push_back(a[i]);
        }
        if(c >> 1 & 1) {
            _xor ^= a[i];
        }
    }
    int sz = val.size();
    bool ok = false;
    if(sz == 0) {
        ok = _xor == 0;
    } else if(sz == 2) {
        ok = _xor == val[0] || _xor == val[1];
    } 
    if(ok) {
        cout << "Menji\n";
    } else {
        cout << "Bot\n";
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
