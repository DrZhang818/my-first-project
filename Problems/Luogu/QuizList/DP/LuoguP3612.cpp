#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s;
    cin >> s;
    ll n;
    cin >> n;
    vector<ll> power;
    int len = s.size();
    power.push_back(len);
    while(power.back() < n) {
        power.push_back(power.back() * 2);
    }
    while(n > len) {
        n--;
        auto pos = upper_bound(power.begin(), power.end(), n) - 1;
        n -= *pos;
        if(n == 0) n = *pos;
    }
    cout << s[n - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
