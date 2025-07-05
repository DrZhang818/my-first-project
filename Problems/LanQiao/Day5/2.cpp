#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


const int MX = 100005;
void solve(){
    vector<int> ok(MX + 1, true);
    ok[1] = false;
    for(int i = 2; i <= MX; i++){
        if(ok[i]){
            for(int j = i * 2; j <= MX; j += i){
                ok[j] = false;
            }
        }
    }
    int a, b;
    cin >> a >> b;
    int ans = 0;
    for(int i = a; i <= b; i++){
        if(ok[i]){
            ans++;
        }
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