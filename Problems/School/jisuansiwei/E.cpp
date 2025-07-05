#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


void solve() { 
    map<string, int> mp;
    string s;
    while(getline(cin, s)) {
        istringstream ss(s);
        string token;
        while(ss >> token) {
            string t;
            for(auto c : token) {
                if(!isalpha(c)) continue;
                t += tolower(c);
            }
            mp[t]++;
        }
    }
    for(auto &[t, c] : mp) {
        cout << t << " " << c << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
