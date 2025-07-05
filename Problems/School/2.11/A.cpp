#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    int cnt = 1;
    for(int i = 0; i < 3; i++) {
        if(s[i + 1] != s[i]) {
            cnt++;
        }
    }
    if(cnt == 2) {
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

