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
    sort(a.begin() + 1, a.end());
    if(a[1] != 0) {
        for(int i = 0; i <= n; i++) {
            cout << 1 << " \n"[i == n];
        }
        return;
    }
    int num = -1;
    for(int i = 1; i <= n; i++) {
        if(i == 1 || a[i] == a[i - 1] || a[i] == a[i - 1] + 1) {
            num = a[i];
        } else {
            break;
        }
    }
    vector<int> cnt(n + 2);
    for(int i = 1; i <= n; i++) {
        if(a[i] == a[i - 1] || a[i] == a[i - 1] + 1) {
            cnt[a[i]]++;
        } else {
            break;
        }
    }
    vector<int> ans(n + 2);
    for(int i = 0; i <= n; i++) {
        if(cnt[i] == 0) break;
        ans[cnt[i]]++;
        ans[n - i + 1]--;
    }   
    ans[0]++;
    ans[n - num]--; 
    for(int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    for(int i = 0; i <= n; i++) {
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

