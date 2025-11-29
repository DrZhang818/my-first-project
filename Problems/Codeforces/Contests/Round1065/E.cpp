#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double; 
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

//2 1 4 6 5 3
void solve() {
    int n;
    cin >> n;
    int x = 0;
    vector<array<int,6>> a ({{2, 1, 4, 6, 5, 3}, {3, 5, 6, 4, 1, 2}});
    for(int i = 0, s = 0; i < n; ) {
        if(n - i < 6) {
            int c = n - i;
            for(int j = 0; j < 6 && c; j++) {
                int num = x + a[s][j];
                if(num > n) {
                    continue;
                }
                cout << num << " ";
                i++;
                c--;
            }
        } else {
            for(int j = 0; j < 6; j++) {
                cout << x + a[s][j] << " ";
            }
            x += 6;
            i += 6; 
        }
        s ^= 1;
    }
    cout << "\n";
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
