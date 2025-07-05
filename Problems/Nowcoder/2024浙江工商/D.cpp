#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    
    string s;
    getline(cin, s);
    string ans;
    for (int i = 0; i < s.length();){
        if(s.substr(i, 3) != "ljl"){
            ans += s[i];
            i++;
        }else{
            ans += "ncljr";
            i += 3;
        }
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    cin.ignore();
    while(n--){
        solve();
    }
    return 0;
}