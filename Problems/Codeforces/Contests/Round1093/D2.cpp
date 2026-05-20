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
    n = n * 2 + 1;

    vector<int> ans;

    for(int t = 1; t <= 3; t++) {
        int l = 0, r = ans.empty() ? n + 1 : ans.back();
        while(l + 1 < r) {
            int mid = l + r >> 1;
            auto Q = ans;
            for(int i = 1; i <= mid; i++) Q.push_back(i);
            if(query(Q) % 2 != Q.size() % 2) {
                r = mid;
            } else {
                l = mid;
            }
        }
        ans.push_back(r);
    }

    answer(ans[2], ans[1], ans[0]);
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