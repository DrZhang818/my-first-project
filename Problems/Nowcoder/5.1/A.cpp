#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/108199/A

//正确做法
const int P = 131;
void solve() {
    int n;
    cin >> n;
    vector<string> ss(n + 1);
    unordered_map<ull,vector<int>> mp;
    vector<int> pos(n + 1), ans(n + 1);
    vector<ull> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> ss[i];
        p[i] = ss[i][0];
        mp[p[i]].push_back(i);
    }
    for(int i = n; i >= 1; i--) {
        ans[i] = mp.size();
        ull H = 0;
        for(int j = 0; j < ss[i].size(); j++) {
            H = H * P + ss[i][j];
            auto it = mp.find(H);
            if(it == mp.end()) continue;
            for(int x : it->second) {
                if(x == i) continue;
                pos[x]++;
                p[x] = p[x] * P + ss[x][pos[x]];
                mp[p[x]].push_back(x);
            }
            mp.erase(it);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
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
