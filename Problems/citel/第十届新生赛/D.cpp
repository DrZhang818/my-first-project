#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;

    int total = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '1'){
            total += 1;
        }
    }
    if(total % 2 && s.back() == '1'){
        cout << "Nigu" << '\n';
        return;
    }
    if(!(total % 2) && s.back() == '0'){
        cout << "Draw" << '\n';
        return ;
    }
    int cnt = 0, dis = 0;
    for(int i = 0; i < n - 1; i++){
        if(s[i] == '1'){
            dis += (n - 1 - (s.back() == '0' ? total : total - 1) + cnt) - i;
            cnt += 1;
        }
    }
    
    if(total % 2){
        if(dis % 2 == 0){
            cout << "Frizea\n";
            return;
        }
        cout << "Nigu\n";
        return;
    }
    if(dis % 2 == 0){
        cout << "Nigu\n";
        return;
    }
    cout << "Draw\n";
    return;  
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}




