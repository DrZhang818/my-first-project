#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i = 1; i <= n * n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    vector<int> ans;
    while(ans.size() < n) {
        auto it = mp.rbegin();
        ans.push_back(it->first);
        if(--it->second == 0) {
            mp.erase(it->first);
        }
        int val = ans.back();
        for(int i = 0; i < ans.size() - 1; i++) {
            int g = gcd(ans[i], val);
            mp[g] -= 2;
            if(mp[g] == 0) {
                mp.erase(g);
            }
        }
    }
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
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
