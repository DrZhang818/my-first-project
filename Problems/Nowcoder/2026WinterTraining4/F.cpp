#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int a, b;
    cin >> a >> b;

    if(a > b) {
        int t = a / (b + 1);
        int rem = a % (b + 1);
        string s(t, '0');
        for(int i = 0; i < b; i++) {
            cout << s;
            if(rem) {
                cout << '0';
                rem--;
            }
            cout << '1';
        }
        cout << s;
        if(rem) {
            cout << '0';
        }
    } else {
        int t = b / (a + 1);
        int rem = b % (a + 1);
        string s(t, '1');
        for(int i = 0; i < a; i++) {
            cout << s;
            if(rem) {
                cout << '1';
                rem--;
            }
            cout << '0';
        }
        cout << s;
        if(rem) {
            cout << '1';
        }
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
