#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000005;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    unordered_map<ll,ll> cnt;
    vector<int> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i];
        cnt[Q[i]] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '+' || a[i][j] == '*') {
                continue;
            }
            ll sum = 0, prod = 1, cur = a[i][j] - '0';
            if(cnt.contains(cur)) {
                cnt[cur]++;
            }
            for(int k = j + 1; k <= m; k++) {
                if(a[i][k] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[i][k] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[i][k] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            for(int k = j - 1; k >= 1; k--) {
                if(a[i][k] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[i][k] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[i][k] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            for(int k = i + 1; k <= n; k++) {
                if(a[k][j] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[k][j] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[k][j] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            for(int k = i - 1; k >= 1; k--) {
                if(a[k][j] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[k][j] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[k][j] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }


            sum = 0, prod = 1, cur = a[i][j] - '0';
            int s = j - i;
            for(int ni = i + 1; ni <= n; ni++) {
                int nj = ni + s;
                if(nj > m) {
                    break;
                }
                 if(a[ni][nj] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[ni][nj] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[ni][nj] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            s = j - i;
            for(int ni = i - 1; ni >= 1; ni--) {
                int nj = ni + s;
                if(nj <= 0) {
                    break;
                }
                 if(a[ni][nj] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[ni][nj] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[ni][nj] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            s = i + j;
            for(int ni = i + 1; ni <= n; ni++) {
                int nj = s - ni;
                if(nj <= 0) {
                    break;
                }
                 if(a[ni][nj] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[ni][nj] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[ni][nj] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }

            sum = 0, prod = 1, cur = a[i][j] - '0';
            s = i + j;
            for(int ni = i - 1; ni >= 1; ni--) {
                int nj = s - ni;
                if(nj > m) {
                    break;
                }
                 if(a[ni][nj] == '+') {
                    if(cur == 0) {
                        break;
                    }
                    sum += prod * cur;
                    prod = 1;
                    cur = 0;
                } else if(a[ni][nj] == '*') {
                    if(cur == 0) {
                        break;
                    }
                    prod *= cur;
                    cur = 0;
                } else {
                    int x = a[ni][nj] - '0';
                    cur = cur * 10 + x;
                    if(cnt.contains(sum + prod * cur)) {
                        cnt[sum + prod * cur]++;
                    }
                }
                if(sum >= int(inf) || prod >= int(inf) || cur >= int(inf)) {
                    break;
                }
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        cout << cnt[Q[i]] << "\n";
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
