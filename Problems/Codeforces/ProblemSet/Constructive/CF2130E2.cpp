#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2130/problem/E2
int query(vector<int> &a) {
    cout << "? " << a.size();
    for(int i : a) {
        cout << " " << i + 1;
    }
    cout << endl;
    int x;
    cin >> x;
    return x;
}
void solve() {
    int n;
    cin >> n;
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = lo + hi >> 1;
        vector<int> a;
        for(int i = 0; i <= mid; i++) {
            a.push_back(i % n);
        }
        if(query(a)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int right = hi % n;
    string ans(n, '?');
    for(int i = 0; i < n; i += 8) {
        vector<int> a;
        for(int j = i; j < min(n, i + 8); j++) {
            int t = 1 << j - i;
            a.insert(a.end(), t, j);
            a.insert(a.end(), t + 1, right);
        }
        int res = query(a);
        for(int j = i; j < min(n, i + 8); j++) {
            if(res >> j - i & 1) {
                ans[j] = '(';
            } else {
                ans[j] = ')';
            }
        }
    }
    cout << "! " << ans << endl;
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
