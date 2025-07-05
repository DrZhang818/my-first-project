#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/1628/problem/A
/*
    贪心 || 二分
    

*/
void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x].push_back(i);
    }
    vector<int> ans;
    for(int i = 1; i <= n; ) {
        int j = i + 1, x = 0;
        while(1) {
            auto it = lower_bound(pos[x].begin(), pos[x].end(), i);
            if(it == pos[x].end()) break;
            x += 1;
            j = max(j, *it + 1);
        }
        i = j;
        ans.push_back(x);
    }
    cout << (int)ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
