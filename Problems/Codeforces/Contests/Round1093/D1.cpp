#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

auto query(const vector<int>& a) {
    int k = a.size();
    cout << "? " << k;
    for(int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

auto answer(int x, int y, int z) {
    cout << "! " << x << " " << y << " " << z << endl;
}

void solve() {
    int n;
    cin >> n;
    n = n << 1 | 1;

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);

    int x, y, z;
    {
        int l = 0, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            vector<int> Q(p.begin() + 1, p.begin() + mid + 1);
            int res = query(Q);
            if(res % 2 != mid % 2) {
                r = mid;
            } else {
                l = mid;
            }
        }
        z = r;
    }

    {
        int l = 0, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            vector<int> Q(p.begin() + mid, p.end());
            int res = query(Q);
            if(res % 2 != (n - mid + 1) % 2) {
                l = mid;
            } else {
                r = mid;
            }
        }
        x = l;
    }

    {
        int l = x, r = z;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            vector<int> L(p.begin() + 1, p.begin() + mid + 1);
            vector<int> R(p.begin() + mid + 1, p.end());
            int u = query(L), v = query(R);
            if(u < v) {
                r = mid;
            } else {
                l = mid;
            }
            y = r;
        }
    }

    answer(x, y, z);
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