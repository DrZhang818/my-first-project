#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, l;
    cin >> n >> l;
    vector<string> ss(n);
    for(int i = 0; i < n; i++){
        cin >> ss[i];
    }
    sort(ss.begin(), ss.end(), [](string &a, string &b)->bool{
        return a + b < b + a;
    });
    string ans;
    for(int i = 0; i < n; i++){
        ans += ss[i];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

