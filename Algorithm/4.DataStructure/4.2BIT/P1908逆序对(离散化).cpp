#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct info {
    int val, id;    
};
class BIT {
private:
    vector<int> a;
    int n;
public:
    BIT(int x) {
        a.resize(x + 1);
        n = x;
    }
    void add(int x, int d) {
        for(int i = x; i <= n; i += i & -i) {
            a[i] += d;
        }
    }
    int query(int x) {
        int res = 0;
        for(int i = x; i > 0; i -= i & -i) {
            res += a[i];
        }
        return res;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].id = i;
    } 
    sort(a.begin(), a.end(), [](auto &a, auto &b) -> bool{
        if(a.val == b.val) return a.id < b.id;
        return a.val < b.val;
    });
    vector<int> rk(n + 1);
    for(int i = 1; i <= n; i++) {
        rk[a[i].id] = i;
    }
    BIT tree(n);
    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        ans += tree.query(rk[i]);
        tree.add(rk[i], 1);
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
    
