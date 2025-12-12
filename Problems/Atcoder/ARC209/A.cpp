#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    int n = s.size();
    s = "#" + s;
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i] == '(' ? 1 : -1);
    }
    bool ok = pre[n] == 0;
    for(int i = 1; i <= n; i++) {
        if(pre[i] < 0) {
            ok = false;
        }
    }
    if(!ok) {
        cout << "First\n";
        return;
    }
    if((n - k) % 2 != 0) {
        cout << "First\n";
        return;    
    } 

    vector<int> nxt(n + 1);
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '(') {
            stk.push(i);
        } else {
            nxt[stk.top()] = i;
            stk.pop();
        }
    }

    int c = 0, c1 = 0, c2 = 0;
    int l, r;
    for(int i = 1; i <= n; i++) {
        if(nxt[i] == n - i + 1) {
            c++;
        } else {
            l = i;
            r = n - i + 1;
            break;
        }
    }
    for(int i = l; i <= r; ) {
        if(s[i] == '(' && s[i + 1] == ')') {
            i += 2;
            c1++;
        } else {
            break;
        }
    }
    for(int i = r; i >= l; ) {
        if(s[i] == ')' && s[i - 1] == '(') {
            i -= 2;
            c2++;
        } else {
            break;
        }
    }

    c += min(c1, c2);
    if(n - 2 * c <= k) {
        cout << "Second\n";
    } else {
        cout << "First\n";
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
