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
    vector<char> a(n + 1);
    vector<int> s, t;
    bool ok = false;
    int u = -1, v = -1, pos = -1;
    for(int l = 1, r = n; l <= r; l++, r--) {
        if(l == r) {
            if(u != -1) {
                cout << "? " << 3 << " " << u << " " << l << " " << u << endl;
                int x;
                cin >> x;
                if(x == 1) {
                    t.push_back(l);
                } else {
                    s.push_back(l);
                }
            } else {
                cout << "? " << 3 << " " << 1 << " " << l << " " << 1 << endl;
                int x;
                cin >> x;
                if(x == 1) {
                    a[l] = (a[1] == '(' ? ')' : '(');
                } else {
                    a[l] = a[1];
                }
            }
            break;
        }
        if(!ok) {
            cout << "? " << 4 << " " << l << " " << r << " " << l << " " << r << endl;
            int x;
            cin >> x;
            if(x == 2) {
                a[l] = '(';
                a[r] = ')';
                if(pos == -1) pos = l;
            } else if(x == 1) {
                a[l] = ')';
                a[r] = '(';
                if(pos == -1) pos = l;
            } else {
                ok = true;
                u = l;
                v = r;
                s.push_back(l);
                s.push_back(r);
            }
        } else {
            cout << "? " << 10 << " " << l << " " << r << " " << l << " " << u << " " << r << " " << l << " " << v << " " << r << " " << l << " " << r << endl;
            int x;
            cin >> x;
            if(x == 4) {
                a[l] = '(';
                a[r] = ')';
                if(pos == -1) pos = l;
            } else if(x == 3) {
                a[l] = ')';
                a[r] = '(';
                if(pos == -1) pos = l;
            } else if(x == 2) {
                t.push_back(l);
                t.push_back(r); 
            } else {
                s.push_back(l);
                s.push_back(r);
            }
        }
    }
    if(!s.empty() && !t.empty()) {
        int i = s[0], j = t[0];
        cout << "? " << 2 << " " << i << " " << j << endl;
        int x;
        cin >> x;
        if(x == 1) {
            for(int k : s) {
                a[k] = '(';
            }
            for(int k : t) {
                a[k] = ')';
            }
        } else {
            for(int k : s) {
                a[k] = ')';
            }
            for(int k : t) {
                a[k] = '(';
            }
        }
    } else if(!s.empty()) {
        int o = s[0];
        assert(pos < 1);

        cout << "? " << 3 << " " << pos << " " << o << " " << pos << endl;
        int x;
        cin >> x;
        char c;
        if(x == 1) {
            c = a[pos] == '(' ? ')' : '(';
        } else {
            c = a[pos];
        }
        for(int k : s) {
            a[k] = c;
        }
    } 
    string ans;
    for(int i = 1; i <= n; i++) {
        ans += a[i];
    }
    cout << "! " << ans << endl;
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
