#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct info {
    int val, id;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].id = i;
    }
    vector<int> tree(n + 1);
    auto add = [&](int x, int d) -> void {
        for(int i = x; i <= n; i += i & -i) {
            tree[i] += d;
        }
    };
    auto query = [&](int x) -> int {
        int res = 0;
        for(int i = x; i > 0; i -= i & -i) {
            res += tree[i];
        }
        return res;
    };
    sort(a.begin() + 1, a.end(), [](auto &a, auto &b) -> bool { 
        if(a.val == b.val) return a.id > b.id;
        return a.val > b.val;
    });
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += query(a[i].id);
        add(a[i].id, 1);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
