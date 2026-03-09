#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= n; j++) {
            a[i][j] = s[j - 1] == '+' ? 1 : -1;
        }
    }
    vector<int> row(n + 1), col(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> row[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> col[i];
    }

    int s1 = accumulate(row.begin() + 1, row.end(), 0);
    int s2 = accumulate(col.begin() + 1, col.end(), 0);
    if(s1 != s2) {
        cout << "No\n";
        return;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i][j] == -1) {
                row[i] += 1;
                col[j] += 1;
            }
        }
    }

    vector<int> C(n + 1);
    iota(C.begin(), C.end(), 0);
    sort(C.begin() + 1, C.end(),
        [&](int i, int j) {
            return col[i] > col[j];
        });

    vector<vector<int>> ans(n + 1, vector<int>(n + 1));
    for(int r = 1; r <= n; r++) {
        int cnt = row[r];
        for(int lo = 1, hi = 1; lo <= n && cnt > 0; lo = hi) {
            if(col[C[lo]] == 0) {
                break;
            }
            while(hi <= n && col[C[hi]] == col[C[lo]]) {
                hi++;
            }
            for(int i = hi - 1; i >= lo && cnt > 0; i--) {
                ans[r][C[i]] = 1;
                col[C[i]]--;
                cnt--;
            }
        }
        if(cnt > 0) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            ans[i][j] = (ans[i][j] == 1) ^ (a[i][j] == -1);
            cout << ans[i][j];
        }
        cout << "\n";
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
