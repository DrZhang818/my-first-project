#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n;
    cin >> n;
    string s = to_string(n);
    string t = s;
    reverse(s.begin(), s.end());
    if(s == t) {
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