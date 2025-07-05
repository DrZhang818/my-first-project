#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    string s;
    while(cin >> s) {
        bool ok = true;
        if(s.size() == 5) {
            if(s[0] == '0' || s[0] == '1') ok = false;
            
            for(char c : s) if(!isdigit(c)) ok = false;

        } else if(s.size() == 7) {
            if(s[0] != '0' || s[2] == '0' || s[2] == '1') ok = false;

            for(char c : s) if(!isdigit(c)) ok = false;

        } else if(s.size() == 8) {
            if(s[0] != '0' || s[3] == '0' || s[3] == '1' || s[2] != '-') ok = false;

            for(int i = 0; i < s.size(); i++) if(!isdigit(s[i]) && i != 2) ok = false;

        } else ok = false;
        if(ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}