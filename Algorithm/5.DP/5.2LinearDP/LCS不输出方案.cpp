#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P1439    
void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        pos[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        b[i] = pos[b[i]];
    }
    vector<int> d;
    d.reserve(n);
    for(int i = 1; i <= n; i++) {
        auto it = lower_bound(d.begin(), d.end(), b[i]);
        if(it == d.end()) {
            d.push_back(b[i]);
        } else {
            *it = b[i];
        }
    }
    cout << d.size() << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
