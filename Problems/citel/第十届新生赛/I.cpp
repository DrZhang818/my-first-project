#include<bits/stdc++.h>
using namespace std;

string s;
vector<int> pos;

void solve1(){
    
    cin >> s;
    int count = 0;
    int n = s.length();
    pos.reserve(n / 2);
    int curi = 0;
    
    for(int i = n - 1; i >= 0; i--){
        
        if(s[i] == 'I'){
            curi++;
        }
        else if(s[i] == 'O' && curi > 0){
            pos.push_back(i);
            count++;
            curi--;
        }
    }
    int ans = 0;
    int l = 0;
    for(int i = pos.size() - 1; i >= 0; i--){
        for(l; l <= pos[i]; l++){
            if(s[l] == 'N' && count > 0){
                ans++;
                count--;
                l++;
                pos[i] = -1;
                break;
            }
        } 
    }
    
    l = 0;
    for(int i = pos.size() - 1; i >= 0; i--){
        if(pos[i] == -1){
            continue;
        }
        bool ok = true;
        for(l; l <= pos[i]; l++){
            if(s[l] == 'I' && count > 0){
                if(curi == 0 && count > 1){
                    count--;
                    curi++;
                }
                if(curi > 0){
                    ans++;
                    count--;
                    curi--;
                    ok = false;
                    l++;
                    break;
                }
            }
        } 
        
        if(ok) {   
            count--;
            curi++;
        }
       
    }
    cout << ans << '\n';
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
   
    solve1();
    return 0;
}