#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++){
        string s;
        getline(cin, s);
        string ans;
        bool ok = false;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '$'){
                ok = !ok;
            }

            if(ok && s[i] != '$'){
                ans += s[i];
            }
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    return 0;
}