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
    vector<vector<int>> ss(n);
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for(int j = 0; j < k; j++) {
            int x;
            cin >> x;
            ss[i].push_back(x);
        }
    }
    vector<int> ans;
    while(!ss.empty()) {
        vector<vector<int>> nss;
        sort(ss.begin(), ss.end());
        for(int x : ss[0]) {
            ans.push_back(x);
        }
        int len = ss[0].size();
        for(auto &s : ss) {
            if(s.size() <= len) {
                continue;
            }
            vector<int> vec;
            for(int i = len; i < s.size(); i++) {
                vec.push_back(s[i]);
            }
            nss.emplace_back(vec);
        }
        swap(ss, nss);
    }
    for(int x : ans) {
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
