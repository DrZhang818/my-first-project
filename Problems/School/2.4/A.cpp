#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int a, b, c;
    cin >> a >> b >> c;
    unordered_map<int,int> mp;
    mp[a]++;
    mp[b]++;
    mp[c]++;
    if(mp[5] == 2 && mp[7] == 1) {
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

