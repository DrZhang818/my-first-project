#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int x, int y) {
    cout << x << " " << y << endl;
    string s;
    cin >> s;
    if(s == "WIN") {
        return 1;
    }
    return 0;
}

void solve() {  
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) {
        for(int j = 2; j <= n; j++) {
            if(query(j - 1, j)) {
                return;
            }
        }
        for(int j = n; j >= 2; j--) {
            if(query(j - 1, j)) {
                return;
            }
        }
    }

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
