#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


unordered_map<string,ull> mp;
void solve() { 
    string s, t;
    cin >> s >> t;
    istringstream ss(s);
    string token;
    ull sum1 = 0, sum2 = 0;
    while(getline(ss, token, '+')) {
        istringstream tk(token);
        ull a;
        string p;
        tk >> a;
        tk >> p;
        sum1 += a * mp[p];
    }
    istringstream tt(t);
    while(getline(tt, token, '+')) {
        istringstream tk(token);
        ull a;
        string p;
        tk >> a;
        tk >> p;
        sum2 += a * mp[p];
    }
    if(sum1 > sum2) {
        cout << "L\n";
    } else if(sum1 < sum2) {
        cout << "T\n";
    } else {
        cout << "=\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    mp["b"] = 1;
    mp["B"] = 8;
    mp["Kb"] = 1000;
    mp["KB"] = 8000;
    mp["Kib"] = 1024;
    mp["KiB"] = 1024 * 8;
    mp["Mb"] = 1000 * mp["Kb"];
    mp["MB"] = 1000 * mp["KB"];
    mp["Mib"] = 1024 * mp["Kib"];
    mp["MiB"] = 1024 * mp["KiB"];
    mp["Gb"] = 1000 * mp["Mb"];
    mp["GB"] = 1000 * mp["MB"];
    mp["Gib"] = 1024 * mp["Mib"];
    mp["GiB"] = 1024 * mp["MiB"];
    mp["Tb"] = 1000 * mp["Gb"];
    mp["TB"] = 1000 * mp["GB"];
    mp["Tib"] = 1024 * mp["Gib"];
    mp["TiB"] = 1024 * mp["GiB"];
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
