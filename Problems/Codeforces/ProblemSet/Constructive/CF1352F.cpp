#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n0, n1, n2;
    cin >> n0 >> n1 >> n2;
    string s = "";
    int idx = 0;
    if(n2){
        for(int i = 0; n2 && i < n2 + 1; i++){
            s += '1';
        }
        for(int i = 0; i < n1; i++){
            s += i % 2 == 0 ? '0' : '1';
        }
        if(s.empty() || s.back() == '0'){    
            for(int i = 0; i < n0; i++){
                s += '0';
            }
        }else{
            for(int i = 0; i < n0; i++){
                s += '0';
                swap(s.back(), s[s.size() - 2]);
            }
        }
    }
    else{
        if(n1 % 2 == 0){
            for(int i = 0; i < n1 + 1; i++){
                s += i % 2 == 0 ? '0' : '1';
            }
        }else{
            for(int i = 0; i < n1 + 1; i++){
                s += i % 2 == 0 ? '1' : '0';
            }
        }
        for(int i = 0; i < n0; i++){
            s += '0';
        }
    }
    cout << s << "\n";
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