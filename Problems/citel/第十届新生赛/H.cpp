#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){   
    int L;
    cin >> L;
    cin.ignore();
    for(int i = 0; i < L; i++){
        string s;
        getline(cin, s);
        if(s == "begin") continue;
        else if(s == "end.") break;
        else {
            if(s.substr(0, 7) == "writeln"){
                for(int i = 9; s[i] != '\''; i++){
                    cout << s[i];
                }
                cout << '\n';
            }
            else{
                for(int i = 7; s[i] != '\''; i++){
                    cout << s[i];
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
