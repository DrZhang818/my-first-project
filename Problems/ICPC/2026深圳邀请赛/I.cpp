#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x;
    cin >> x;
    vector<int> a;
    if(1 <= x && x <= 8) {
        cout << "Yes\n";
        for(int i = 0; i <= 8; i++) {
            if(i != x) {
                a.push_back(i);
            }
        }
        while(a.size() < 12) a.push_back(0);
        for(int i = 0; i < 12; i++) {
            cout << a[i] << " \n"[i == 11];
        }
    } else if(x == 11) {
        cout << "Yes\n";
        for(int i = 0; i < 6; i++) {
            cout << i << " ";
        }
        cout << "0 0 0 6 7 8\n";
    } else if(x == 22) {
        cout << "Yes\n";
        for(int i = 0; i < 6; i++) {
            cout << i << " ";
        }
        cout << "0 1 0 6 7 8\n";
    } else if(x == 33) {
        cout << "Yes\n";
        for(int i = 0; i < 6; i++) {
            cout << i << " ";
        }
        cout << "0 1 2 6 7 8\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}