#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int to[3][3];
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    /*
        a->b 1
        b->c 2
        a->c 3
        b->a 4
        c->b 5
        c->a 6
    */
    to[0][1] = 1, to[1][2] = 2, to[0][2] = 3;
    to[1][0] = 4, to[2][1] = 5, to[2][0] = 6;
    int c1 = 0, c2 = 0;
    vector<set<int>> st(7);
    for(int i = 1; i <= q; i++) {
        char a, b;
        cin >> a >> b;
        int x = a - 'a', y = b - 'a';
        st[to[x][y]].insert(i);
    }
    for(int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        if(x == 0) continue;
        if(x == 1) {
            if(!st[4].empty()) {
                s[i] = 'a';
                st[4].erase(*st[4].begin());
            } else {
                if(!st[2].empty() && !st[6].empty()) {
                    int t1 = *st[2].begin();
                    auto it = st[6].lower_bound(t1);
                    if(it != st[6].end()) {
                        s[i] = 'a';
                        st[2].erase(t1);
                        st[6].erase(it);
                    } 
                }
            }
        } else {
            if(!st[6].empty()) {
                s[i] = 'a';
                st[6].erase(*st[6].begin());
            } else {
                int t1 = -1;
                if(!st[5].empty()) {
                    t1 = *st[5].begin();
                    s[i] = 'b';
                    st[5].erase(t1);
                }
                if(t1 != -1 && !st[4].empty()) {
                    auto it = st[4].lower_bound(t1);
                    if(it != st[4].end()) {
                        s[i] = 'a';
                        st[4].erase(it);
                    }
                }
            }
        }
    }
    cout << s << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
