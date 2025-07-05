#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int id, o;
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    vector<info> ans;
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    for(int i = 1, flag = 0; i <= n; i += flag, flag ^= 1) {
        int idx = 1, cur = i + n * flag;
        while(a[idx] != cur) idx++;
        if((cur <= n) ^ (idx <= n)) {
            if(idx > n) {
                ans.emplace_back(3, idx - n);
                swap(a[idx], a[idx - n]);
                idx -= n;
            } else {
                ans.emplace_back(3, idx);
                swap(a[idx], a[idx + n]);
                idx += n;
            }
        } 
        for(; idx > cur; idx--) {
            if(idx > n) {
                ans.emplace_back(2, idx - n - 1);
            } else {
                ans.emplace_back(1, idx - 1);
            }
            swap(a[idx - 1], a[idx]);
        }
    }
    cout << ans.size() << "\n";
    for(auto &[id, o] : ans) {
        cout << id << " " << o << "\n";
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
