#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct enemy{
    int A;
    int B;
    ll dam;
};
void solve(){
    ll len, n, hp;
    scanf("%lld %lld %lld", &len, &n, &hp);
    char s[200005];
    scanf("%s", s);
    ll temp = hp;
    enemy e;
    ll base_dam = 1;
    vector<vector<ll>> state(2, vector<ll>(2, 0));
    for(int n = 0; n <= 1; n++){
        for(int m = 0; m <= 1; m++){
            ll cur_dam = 0;
            if(m){
                if(len <= 4){
                    cur_dam = 0;
                }
                else{
                    cur_dam += (len - 4) * base_dam;
                }
            } 
            else{   
                int state1 = 0, state2 = 0;
                if(!n){
                    for(int i = 0; i < len; i++){
                        if(s[i] == 'E'){
                            state2 = 5;
                        }

                        if(i >= 4 && state2 == 0){
                            cur_dam += base_dam;
                        }
                        state2 = max(0, state2 - 1);
                    }
                }
                else{
                    for(int i = 0; i < len; i++){
                        if(s[i] == 'R'){
                            state1 = 3;
                        }
                        else if(s[i] == 'E'){
                            state2 = 5;
                        }
                        if(i >= 4 && (state1 == 0 || state2 == 0)){
                            cur_dam += base_dam;
                        }
                        state1 = max(0, state1 - 1);
                        state2 = max(0, state2 - 1);
                    }
                }
            }
            state[n][m] = cur_dam;
        }
    }
    for(int i = 0; i < n; i++){
        hp = temp;
        scanf("%d %d %lld", &e.A, &e.B, &e.dam);
        hp -= e.dam * state[e.A][e.B];
        if(hp > 0){
            printf("WIN %lld\n", hp);
        }else{
            printf("LOSE %lld\n", hp);
        }
    }
}

int main()
{
    solve();
    return 0;
}