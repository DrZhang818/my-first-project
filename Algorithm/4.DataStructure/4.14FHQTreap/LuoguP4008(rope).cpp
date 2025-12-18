#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

crope R;
char buf[2000005];

void solve() {  
    int q;
    cin >> q;
    int pos = 0;
    while(q--) {
        string op;
        cin >> op;
        if(op[0] == 'M') {
            cin >> pos;
        } else if(op[0] == 'I') {
            int n;
            cin >> n;
            int i = 0;
            while(i < n) {
                char ch = cin.get();
                if(32 <= ch && ch <= 126) {
                    buf[i++] = ch;
                }
            }
            buf[i] = '\0';
            R.insert(pos, buf);
        } else if(op[0] == 'D') {
            int n;
            cin >> n;
            R.erase(pos, n);
        } else if(op[0] == 'G') {
            int n;
            cin >> n;
            cout << R.substr(pos, n) << "\n";
        } else if(op[0] == 'P') {
            pos--;
        } else {
            pos++;
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
