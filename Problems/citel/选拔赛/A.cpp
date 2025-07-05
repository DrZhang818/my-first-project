#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    string s;
    cin >> s;
    if(s == "ycy" || s == "Ycy" || s == "yCy" || s == "YCy" || s == "ycY" || s == "YcY"|| s=="YCY"|| s=="yCY"){
        cout << "ERROR\n";
    }else{
        s += "txdy";
        cout << s << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}