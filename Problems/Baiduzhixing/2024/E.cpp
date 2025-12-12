#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

void solve() {  
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto cal = [&](int k, int d) -> int {
        int lo = inf, hi = 0;
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            lo = min(lo, a[i]);
            hi = max(hi, a[i]);
            if(hi - lo > d) {
                k--;
                lo = a[i];
                hi = a[i];
            }
            if(k <= 0) {
                break;
            }
            cnt++;
        }
        return cnt;
    };
    int l = -1, r = inf;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(cal(k, mid) == n) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
    l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(cal(mid, d) == n) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";

    const int N = 20;
    vector<array<int,N>> go(n + 1);
    for(int i = 1; i <= n; i++) {
        fill(go[i].begin(), go[i].end(), n + 1);
    }
    deque<int> mn, mx;
    for(int l = 1, r = 1; r <= n; r++) {
        while(!mn.empty() && a[r] <= a[mn.back()]) {
            mn.pop_back();
        }
        while(!mx.empty() && a[r] >= a[mx.back()]) {
            mx.pop_back();
        }
        mn.push_back(r);
        mx.push_back(r);
        while(a[mx.front()] - a[mn.front()] > d) {
            go[l][0] = r;
            l++;
            if(mn.front() < l) mn.pop_front();
            if(mx.front() < l) mx.pop_front();
        }
    }
    for(int s = 1; s < N; s++) {
        for(int i = 1; i <= n; i++) {
            if(go[i][s - 1] != n + 1) {
                go[i][s] = go[go[i][s - 1]][s - 1];
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = i, rem = k;
        for(int s = N - 1; s >= 0 && j <= n; s--) {
            if(rem >= 1 << s) {
                j = go[j][s];
                rem -= 1 << s;
            }
        }
        ans = max(ans, j - i);
    }
    cout << ans << "\n";
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
