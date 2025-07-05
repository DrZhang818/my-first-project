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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int cur = 1, flag = 1, l = 1, r = n;
    vector<int> ans(n + 1);
    while(l != r) {
        int cnt = 0;
        for(int i = 1; i <= n; i++) if(a[i] == cur) cnt++;
        bool ok = true;
        if(flag & 1) {
            int lo = r - cnt + 1, t = lo; 
            for(int i = 1; i <= n; i++) {
                if(a[i] == -1) {
                    ok = false;
                } 
                if(ok && a[i] == cur) {
                    ans[i] = r--;
                } else if(a[i] == cur) {
                    ans[i] = lo++;
                }
            }
            r = t - 1;
        } else {
            int hi = l + cnt - 1, t = hi;
            for(int i = n; i >= 1; i--) {
                if(a[i] == -1) {
                    ok = false;
                } 
                if(ok && a[i] == cur) {
                    ans[i] = l++;
                } else if(a[i] == cur) {
                    ans[i] = hi--;
                }
            }
            l = t + 1;
        }
        flag ^= 1;
        cur++;
    }
    for(int i = 1; i <= n; i++) if(a[i] == -1) ans[i] = l;
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
