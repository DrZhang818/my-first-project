#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

int n, l, r;  
bool check(int x) {
    int res = 0;
    while(x) { 
        res += x % 10;
        x /= 10;
    }
    return res >= l && res <= r;
}
void solve() { 
    cin >> n >> l >> r;
    int ans = 0;
    for(int i = 1; i <= n; i++) if(check(i)) ans += i; 
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
