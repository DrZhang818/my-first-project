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
    string s, t;
    cin >> s >> t;
    s = "#" + s, t = "#" + t;
    vector<int> ans;
    for(int i = n, l = 1, r = n, tag = 0; i >= 1; i--) {
        if(!tag) {
            if((s[l] ^ tag) == t[i]) {
                ans.push_back(1);
            }
            ans.push_back(i);
            l++;
        } else {
            if((s[r] ^ tag) == t[i]) {
                ans.push_back(1);
            }
            ans.push_back(i);
            r--;
        }
        tag ^= 1;
    }
    cout << ans.size() << " ";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
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
