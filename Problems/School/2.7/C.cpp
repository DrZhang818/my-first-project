#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> neg, pos;
    int need = k;
    neg.push_back(0);
    pos.push_back(0);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(x == 0) need -= 1;
        else if(x > 0) pos.push_back(x);
        else if(x < 0) neg.push_back(-x);
    }
    if(need == 0) {
        cout << 0 << "\n";
        return;
    }
    sort(neg.begin(), neg.end());
    ll ans = 10000000000;
    for(int i = 0; i < min(need, (int)pos.size()); i++) {
        if(need - i >= neg.size()) continue;
        ans = min(ans, (ll)2 * pos[i] + neg[need - i]);
    }
    for(int i = 0; i < min(need, (int)neg.size()); i++) {
        if(need - i >= pos.size()) continue;
        ans = min(ans, (ll)2 * neg[i] + pos[need - i]);
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

