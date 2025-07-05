#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<vector<int>> tr;
inline int lowbit(int o) { return o & -o; }
int n;
void add(int id, int o, int d) {    
    for(; o <= n; o += lowbit(o)) {
        tr[id][o] += d;
    }
}
int query(int id, int o) {
    int res = 0;
    for(; o > 0; o -= lowbit(o)) {
        res += tr[id][o];
    }
    return res;
}
void solve() {
    cin >> n;
    tr.resize(26, vector<int>(n + 1));
    string s;
    cin >> s;
    s = "#" + s;
    for(int i = 1; i <= n; i++) {
        int id = s[i] - 'a';
        add(id, i, 1);
    }
    int q;
    cin >> q;
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int pos;
            char c;
            cin >> pos >> c;
            add(s[pos] - 'a', pos, -1);
            s[pos] = c;
            add(s[pos] - 'a', pos, 1);
        } else {
            int l, r;
            cin >> l >> r;
            int cnt = 0;
            for(int i = 0; i < 26; i++) {
                if(query(i, r) > query(i, l - 1)) {
                    cnt++;
                }
            }
            cout << cnt << "\n";
        }
    }    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
