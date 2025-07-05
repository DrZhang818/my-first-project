#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

char c[3] = {'A', 'B', 'C'};
void solve(){
    string s;
    cin >> s;
    char pre = 'A' - 1;
    bool ok = true;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == pre){
            ok = false;
            break;
        }
        if(s[i] == '?'){
            if(i + 1 < s.length()){
                for(int j = 0; j < 3; j++){
                    if(c[j] != pre && c[j] != s[i + 1]){
                        s[i] = c[j];
                        break;
                    }
                }    
            }
            else{
                s[i] = (pre + 1 == 'D') ? 'A' : pre + 1;
            }
        }
        pre = s[i];
    }
    if(!ok){
        cout << -1 << "\n";
        return;
    }
    cout << s << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}