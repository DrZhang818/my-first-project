#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

int n;

/*
0: .
1: +
2: -
3: ?
*/

void solve() {
    int m, tot_penalty;
    cin >> m >> tot_penalty;

    int ac = 0;
    i64 penalty = 0;

    vector<int> state(n + 1), cnt(n + 1), time(n + 1);
    vector<int> pre(n + 1), suf(n + 1);
    vector<int> vec;

    for(int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if(c == '.') continue;
        if(c == '+') {
            int x, y;
            char tmp;
            cin >> x >> tmp >> y;
            ac++;
            penalty += 20 * (x - 1) + y;
            state[i] = 1;
            cnt[i] = x;
            time[i] = y;
        } else if(c == '-') {
            int x;
            cin >> x;
            state[i] = 2;
            cnt[i] = x;
        } else {
            int x, y;
            cin >> x >> y;
            vec.push_back(i);
            state[i] = 3;
            tie(pre[i], suf[i]) = pair{y - x, x};
        }
    }

    int sz = int(vec.size());

    if(ac > m || penalty > tot_penalty || ac + sz < m) {
        cout << "No\n";
        return;
    }

    bool ok = false;
    for(int s = 0; s < 1 << sz; s++) {
        if(__builtin_popcount(s) != m - ac) {
            continue;
        }

        i64 cur_penalty = penalty;
        int canUsed = 0;
        for(int p = 0; p < sz; p++) {
            if(~s >> p & 1) continue;
            int i = vec[p];
            cur_penalty += pre[i] * 20;
            canUsed += suf[i];
        }

        if(cur_penalty > tot_penalty) continue;

        int dis = tot_penalty - cur_penalty;

        i64 lo = 240 * (m - ac);
        i64 hi = min(dis, 299 * (m - ac));
        hi -= ((hi - dis) % 20 + 20) % 20;


        if(hi < lo) continue;

        int need = m - ac + (dis - hi) / 20;

        if(need > canUsed) continue;

        for(int p = 0; p < sz; p++) {
            if(s >> p & 1) {
                cnt[vec[p]] = 1;
                time[vec[p]] = 240;
                need--;
                hi -= 240;
            }
        }

        for(int p = 0; p < sz; p++) {
            int i = vec[p];
            if(s >> p & 1) {
                state[i] = 1;

                cnt[i] += pre[i] + min(need, suf[i] - 1);
                need -= min(need, suf[i] - 1);

                time[i] += min(59LL, hi);
                hi -= min(59LL, hi);
            } else {
                state[i] = 2;
                cnt[i] = pre[i] + suf[i];
            }
        }

        ok = true;
        break;
    }

    if(!ok) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";

    for(int i = 1; i <= n; i++) {
        if(state[i] == 0) {
            cout << ".\n";
        } else if(state[i] == 1) {
            cout << "+ " << cnt[i] << "/" << time[i] << "\n";
        } else if(state[i] == 2) {
            cout << "- " << cnt[i] << "\n";
        }
        assert(state[i] != 3);
    }  
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t >> n;
    while(t--) {
        solve();
    }
    return 0;
}