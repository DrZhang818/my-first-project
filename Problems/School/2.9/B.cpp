#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    string s;
    cin >> s;
    unordered_map<char,int> mp;
    bool ok = true;
    for(auto c : s) mp[c]++;
    for(auto it = mp.begin(); it != mp.end(); it++){
        int cnt = it->second;
        if(cnt % 2 != 0) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << "Yes\n";
    }else{
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

