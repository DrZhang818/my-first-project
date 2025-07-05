#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://loj.ac/p/10114
constexpr int MX = 32005;
vector<int> bit(MX);
void add(int i) {
    for(; i < MX; i += (i & -i)) bit[i] += 1;
}
int query(int i) {
    ll res = 0;
    for(; i > 0; i -= (i & -i)) res += bit[i];
    return res;
}
void solve() { 
    int n;
    cin >> n;
    vector<int> ans(n);

    while(n--) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        int tot = query(x);
        ans[tot]++;
        add(x);
    }
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
