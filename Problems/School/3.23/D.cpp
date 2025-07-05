#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


inline int lowbit(int o) { return o & -o; }
vector<ll> tr;
constexpr int N = 3000;
void add(int o) {
    for(; o <= N; o += lowbit(o)) tr[o] += 1;
}
ll query(int o) {
    ll res = 0;
    for(; o > 0; o -= lowbit(o)) res += tr[o];
    return res;
}
void solve() { 
    int n;
    cin >> n;
    tr.resize(N + 1, 0);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }   
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += query(N) - query(a[i]);
        for(int j = 1; j < i; j++) {
            add(a[i] + a[j]);
        }
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
    
    