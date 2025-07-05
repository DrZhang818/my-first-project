#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k, m;
    string s;
    cin >> n >> k >> m >> s;
    s = "#" + s;
    string ans;
    vector<int> occ(k); 
    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        cnt += occ[s[i] - 'a'] == 0;
        occ[s[i] - 'a'] = 1;
        if(cnt == k) {
            ans += s[i];
            cnt = 0;
            for(int i = 0; i < k; i++) occ[i] = 0;
        }
        if(ans.size() == n) break;
    }
    if(ans.size() == n) {
        cout << "Yes\n";
    } else {
        for(int i = 0; i < k; i++) {
            if(!occ[i]) {
                while(ans.size() < n) ans += 'a' + i;
                break;
            }
        }
        cout << "No\n" << ans << "\n";
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
    