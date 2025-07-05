#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<int> a;
void add(int i) {
    for(; i <= n; i += i & -i) a[i] ^= 1;
}
int query(int i) {
    int res = 0;
    for(; i > 0; i -= i & -i) res ^= a[i];
    return res;
}
void solve() { 
    int m;
    cin >> n >> m;
    a.resize(n + 5);
    while(m--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int x, y;
            cin >> x >> y;
            add(x);
            add(y + 1);
        } else {
            int x;
            cin >> x;
            cout << query(x) << "\n";
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
    
