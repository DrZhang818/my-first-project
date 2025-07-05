#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    string s1, s2, t1, t2;
    cin >> s1 >> s2 >> t1 >> t2;
    int c10 = 0, c11 = 0, c20 = 0, c21 = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(t1[i] == '0' && t2[i] == '0'){
            ans += (s1[i] == s2[i]);
        }
        else{
            if(t1[i] == '1'){
                c10 += s1[i] == '0';
                c11 += s1[i] == '1';
            }
            if(t2[i] == '1'){
                c20 += s2[i] == '0';
                c21 += s2[i] == '1';
            }
        }
    }
    for(int i = 0; i < n; i++){
        if((t1[i] - '0') ^ (t2[i] - '0') == 1){
            int flag = (t1[i] - '0') ? 1 : 2;   
            int t = s1[i] - '0';
            if(s1[i] == s2[i]){
                if(t == 0){
                    flag == 1 ? (c10 > 0 ? c10--, ans++ : c10) : (c20 > 0 ? c20--, ans++ : c20);
                } 
                else{
                    flag == 1 ? (c11 > 0 ? c11--, ans++ : c11) : (c21 > 0 ? c21--, ans++ : c21);
                }
            }     
            else{
                if(t == 0){
                    flag == 1 ? (c11 > 0 ? c11--, ans++ : c11) : (c20 > 0 ? c20--, ans++ : c20);
                } 
                else{
                    flag == 1 ? (c10 > 0 ? c10--, ans++ : c10) : (c21 > 0 ? c21--, ans++ : c21);
                }
            }
        }
    }
    cout << c10 << " " << c20 << "\n" << c11 << " " << c21 << "\n";
    ans += min(c10, c20) + min(c11, c21);
    cout << ans << "\n";
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