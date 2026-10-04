#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());

    int k = n - m;
    i64 need = 0;
    for(int i = 1; i <= m; i++) {
        if(a[k + i] > b[i]) {
            cout << -1 << "\n";
            return;
        }
        need += b[i] - a[k + i];
    }

    if(need > k) {
        cout << -1 << "\n";
        return;
    }

    priority_queue<int, vector<int>, greater<int>> small(a.begin() + 1, a.begin() + k + 1);
    priority_queue<int, vector<int>, greater<int>> large(a.begin() + k + 1, a.end());

    vector<int> ans;
    while(!small.empty() && small.size() > need) {
        int x = small.top();
        small.pop();
        ans.push_back(x);

        large.push(x + 1);

        int y = large.top();
        large.pop();
        small.push(y);
        small.pop();

        need += y - (x + 1);
    }

    bool ok = need == small.size();
    vector<int> c(m + 1);
    for(int i = 1; i <= m; i++) {
        int x = c[i] = large.top(); large.pop();
        int y = b[i];
        if(x > y) {
            ok = false;
            break;
        }
    }

    if(!ok) {
        cout << -1 << "\n";
        return;
    }

    for(int i = m; i >= 1; i--) {
        for(int x = c[i]; x < b[i]; x++) {
            ans.push_back(x);
        }
    }

    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
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
