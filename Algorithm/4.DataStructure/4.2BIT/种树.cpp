#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<int> t1, t2;
void add(vector<int> &a, int i) {
    for(; i <= n; i += i & -i) a[i]++;
}
int query(vector<int> &a, int i) {
    int res = 0;
    for(; i > 0; i -= i & -i) res += a[i];
    return res;
}
void solve() { 
    int q;
    cin >> n >> q;
    t1.resize(n + 5);
    t2.resize(n + 5);
    while(q--) {
        int flag, l, r;
        cin >> flag >> l >> r;
        if(flag == 1) {
            add(t1, l);
            add(t2, r);
        } else {
            int ans = query(t1, r) - query(t2, l - 1);
            cout << ans << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
