#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/problemset/problem/538/B
/*
    贪心 || 数位DP

*/
void solve(){
    string s;
    cin >> s;
    int len = s.size();
    vector<int> a(len);
    int mx = 0;
    for(int i = 0; i < len; i++){
        int cur = s[i] - '0';
        a[i] = cur;
        mx = max(mx, cur);
    }
    cout << mx << "\n";
    for(int i = 0; i < mx; i++){
        bool ok = false;
        for(int j = 0; j < len; j++){
            if(a[j] > 0){
                cout << 1;
                ok = true;
            }else if(ok){
                cout << 0;
            }
            a[j]--;
        }
        cout << " ";
    }
    cout << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
