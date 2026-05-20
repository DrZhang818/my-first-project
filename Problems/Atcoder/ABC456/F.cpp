#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr i64 inf = 1E18;

struct Mat {
    i64 a[2][2];

    Mat(i64 x = -inf) {
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = x;
    }
};

Mat id() {
    Mat x;
    x.a[0][0] = x.a[1][1] = 0;
    return x;
}

Mat single(i64 x) {
    Mat m;
    m.a[0][0] = 0;
    m.a[0][1] = 0;
    m.a[1][0] = x;
    return m;
}

Mat operator+(const Mat& a, const Mat& b) {
    Mat c;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                c.a[i][j] = max(c.a[i][j], b.a[i][k] + a.a[k][j]);
            }
        }
    }
    return c;
}

// struct SegmentTree {
//     int n;
//     vector<Mat> tr;

//     SegmentTree(const vector<i64>& a) {
//         int m = a.size();
//         n = 1;
//         while(n < m) n <<= 1;
//         tr.assign(n << 1, id());
//         for(int i = 0; i < m; i++) {
//             tr[n + i] = single(a[i]);
//         }
//         for(int i = n - 1; i; i--) {
//             tr[i] = tr[i << 1] + tr[i << 1 | 1];
//         }
//     }

//     Mat rangeQuery(int l, int r) {
//         Mat x = id(), y = id();
//         for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
//             if(l & 1) x = x + tr[l++];
//             if(r & 1) y = tr[--r] + y;
//         }
//         return x + y;
//     }
// };

struct Swag {
    vector<pair<Mat, Mat>> l, r;

    int size() const {
        return l.size() + r.size();
    }

    void push(const Mat& x) {
        Mat p = r.empty() ? x : r.back().second + x;
        r.push_back({x, p});
    }

    void pop() {
        if(l.empty()) {
            while(!r.empty()) {
                Mat x = r.back().first;
                r.pop_back();

                Mat p = l.empty() ? x : x + l.back().second;
                l.push_back({x, p});
            }
        }
        l.pop_back();
    }

    Mat prod() const {
        if(l.empty()) {
            return r.back().second;
        }
        if(r.empty()) {
            return l.back().second;
        }
        return l.back().second + r.back().second;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<i64> a(n), pre(n + 1);
    vector<Mat> mat(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
        mat[i] = single(a[i]);
    }

    i64 ans = inf;

    auto work = [&](int len) {
        if(len > n) return;

        int w = len - 2;

        if(w <= 0) {
            for(int i = 0; i + len <= n; i++) {
                ans = min(ans, pre[i + len] - pre[i]);
            }
            return;
        }

        Swag q;
        for(int i = 1; i <= w; i++) {
            q.push(mat[i]);
        }

        for(int l = 0; l + len <= n; l++) {
            i64 sum = pre[l + len] - pre[l];

            Mat p = q.prod();
            ans = min(ans, sum - max(p.a[0][0], p.a[1][0]));

            if(l + len < n) {
                q.pop();
                q.push(mat[l + len - 1]);
            }
        }
    };    

    work(k);
    work(k + 1);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}