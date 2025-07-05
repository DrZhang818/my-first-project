#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n;
vector<int> a;
void add(int i, int x) {
    for(; i <= n; i += i & -i) a[i] += x;
}
ll query(int i) {
    ll res = 0;
    for(; i > 0; i -= i & -i) res += a[i];
    return res;
}  
void solve() { 
    int k;
    cin >> n >> k;
    a.resize(n + 5);
    while(k--) {
        char op;
        cin >> op;
        if(op == 'A') {
            int m;
            cin >> m;
            cout << query(m) << "\n";
        } else if(op == 'B') {
            int m, x;
            cin >> m >> x;
            add(m, x);
        } else {
            int m, x;
            cin >> m >> x;
            add(m, -x);
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
    
