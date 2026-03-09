#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

auto query(vector<int>& a) {
    cout << "? " << a.size();
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    assert(res != -1);
    return res;
};

constexpr int N = 30000;

void solve() {  
    vector<int> res;
    vector<int> range {3, 6, 8, 10};
    for(int p : range) {
        vector<int> Q;
        for(int v = 1; v <= N; v *= p) {
            Q.push_back(v);
        }
        res.push_back(query(Q));
    }

    auto calc = [&](int x, int p) {
        int sum = 0;
        while(x) {
            sum += x % p;
            x /= p;
        }
        return sum;
    };

    vector<int> a;
    for(int i = 1; i <= N; i++) {
        bool ok = true;
        for(int j = 0; j < 4; j++) {
            int p = range[j];
            if(calc(i, p) != res[j]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            a.push_back(i);
        }
    }

    auto ck = [&](int l, int r) {
        vector<int> Q;
        for(int i = 1; i < a[l]; i <<= 1) {
            Q.push_back(i);
        }
        for(int i = l; i < r; i++) {
            Q.push_back(a[i]);
        }
        int cur = query(Q);
        return cur == 1;
    };

    int l = 0, r = a.size();

    while(l < r) {
        int mid = l + r >> 1;
        if(ck(mid, r)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    cout << "! " << a[l - 1] << endl;
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
