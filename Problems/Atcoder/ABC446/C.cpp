#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, d;
    cin >> n >> d;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int sum = 0;
    deque<pair<int,int>> dq;
    for(int i = 1; i <= n; i++) {
        dq.emplace_back(a[i], i);
        sum += a[i];
        sum -= b[i];
        int need = b[i];
        while(need > 0) {
            auto [cnt, j] = dq.front();
            dq.pop_front();
            int t = min(need, cnt);
            need -= t;
            cnt -= t;
            if(cnt > 0) {
                dq.emplace_front(cnt, j);
            }
        }
        while(!dq.empty() && i - dq.front().second >= d) {
            sum -= dq.front().first;
            dq.pop_front();
        }
    }
    cout << sum << "\n";

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
