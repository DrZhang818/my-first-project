#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1474/C
void solve() {
    int n;
    cin >> n;
    n *= 2;
    vector<int> a(n + 1);
    unordered_map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    sort(a.begin() + 1, a.end());
    auto ck = [&](int i) -> bool {
        auto t = mp;
        int cur = a[i] + a[n];
        bool ok = true;
        for(int r = n; r >= 1; r--) {
            if(t[a[r]] == 0) continue;
            if(cur - a[r] == a[r] && t[a[r]] == 1 || t[cur - a[r]] == 0) {
                ok = false;
                break;
            }
            t[a[r]]--;
            t[cur - a[r]]--;
            cur = a[r];
        }
        return ok;
    };
    for(int i = 1; i <= n - 1; i++) {
        if(ck(i)) {
            cout << "YES\n";
            int cur = a[i] + a[n];
            cout << a[i] + a[n] << "\n";
            for(int r = n; r >= 1; r--) {
                if(mp[a[r]] == 0) continue;
                mp[a[r]]--;
                mp[cur - a[r]]--;
                cout << a[r] << " " << cur - a[r] << "\n";
                cur = a[r];
            }
            return;
        } 
    }
    cout << "NO\n";
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
