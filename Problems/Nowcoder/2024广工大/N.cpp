#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    int ans = 0;
    string MS;
    while(n--){
        string s;
        cin >> s;
        int cur;
        cin >> cur;
        if(cur > ans){
            ans = cur;
            MS = s;
        }
    }
    cout << MS << "\n";
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
