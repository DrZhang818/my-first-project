#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int x, id;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end(), [&](auto x, auto y) -> bool{
        return x.x < y.x;
    }); 
    for(int i = 1; i <= n; i++) {
        cout << a[i].id << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
