#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    auto dfs = [&](auto &&self, int l, int r) -> void {
        if(l == r) {
            return ;
        }
        int mid = l + r >> 1;
        self(self, l, mid);
        self(self, mid + 1, r);
        if(a[l] > a[mid + 1]) {
            for(int L = l, R = mid + 1; L <= mid; L++, R++) {
                swap(a[L], a[R]);
            }
        }
    };
    dfs(dfs, 0, (1 << n) - 1);
    for(int i = 0; i < 1 << n; i++) {
        cout << a[i] << " \n"[i == (1 << n) - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
