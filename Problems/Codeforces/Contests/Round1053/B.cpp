#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    set<int> st;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        st.insert(x);
    }
    int cur = 1;
    for(char c : s) {
        if(c == 'A') {
            cur++;
            st.insert(cur);
        } else {
            cur++;
            while(st.contains(cur)) {
                cur++;
            }
            st.insert(cur);
            cur++;
            while(st.contains(cur)) {
                cur++;
            }
        }
    }
    cout << st.size() << "\n";
    for(int x : st) {
        cout << x << " ";
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
