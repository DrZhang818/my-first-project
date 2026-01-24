#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

inline int lowbit(int o) { return o & -o; }

struct FenwickTree {
    int n;
    vector<int> cnt;
    vector<ll> sum;
    FenwickTree(int n) : n(n), cnt(n), sum(n) {}
    void add(int o, int d) {
        for(int x = o; x < n; x += lowbit(x)) {
            cnt[x] += d;
            sum[x] += (ll)o * d;
        }
    }
    int queryCnt(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += cnt[o];
        }
        return res;
    }
    ll querySum(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += sum[o];
        }
        return res;
    }
    int kth(int k) {
        int x = 0;
        ll cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + cnt[x + i] < k) {
                x += i;
                cur += cnt[x];
            }
        }
        return x + 1;
    }
    ll query(int k) {
        int v = kth(k);
        return querySum(v - 1) + ll(k - queryCnt(v - 1)) * v;
    }
};

void solve() {  
    int n, q;
    cin >> n >> q;
    FenwickTree fen(N + 1), fen2(N + 1);


    vector<int> A(n + 1), B(n + 1);
    ll sum = 0;
    int cnt = 0;

    auto upd = [&](int x, int type, int d) {
        sum += x * d;
        if(type == 1) {
            fen2.add(x, d);
        } else {
            cnt += d;
        }
        fen.add(x, d);
    };  

    for(int i = 1; i <= n; i++) {
        cin >> A[i] >> B[i];
        upd(A[i], B[i], 1);
    }

    while(q--) {
        int i, x, y;
        cin >> i >> x >> y;
        upd(A[i], B[i], -1);

        A[i] = x;
        B[i] = y;
        upd(A[i], B[i], 1);

        ll ans = sum;
        if(cnt == n) {
            ans += sum - fen.query(1);
        } else if(cnt) {
            ans += sum - fen.query(n - cnt);
            int x = fen.kth(n - cnt + 1);
            int y = fen2.kth(n - cnt);
            if(y < x) {
                ans += y - x;
            }
        }

        cout << ans << "\n";
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
