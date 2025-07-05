#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://citel.bjtu.edu.cn/acm/problem/2045
/*
    字符串模拟
*/
void solve(){
    int n;
    cin >> n;
    vector<string> ss(n);
    for(int i = 0; i < n; i++){
        cin >> ss[i];
    }
    int ans = 0;
    for(int j = 0; j < 7; j++){
        for(int i = 0; i < n;){
            if(ss[i][j] == '|') break;
            if(ss[i][j] == '_') {
                i += 1;
                continue;
            }
            if(ss[i][j] == '#' && i + 1 < n && ss[i + 1][j] == '#'){
                ans++;
                i += 2;
            }
            else{
                ans++;
                i += 1;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}