#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


const int MOD = 1000000007;
const int MX = 1005;
ll binpow(ll a, ll b, ll m = MOD){
    ll res = 1;
    a %= m;
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll a){
    return binpow(a, MOD - 2, MOD);
}

static ll fact[MX + 1], invfact[MX + 1];
void init_factorials(){
    fact[0] = 1;
    for(int i = 1; i <= MX; i++){
        fact[i] = fact[i - 1] * i % MOD;
    }
    invfact[MX] = inv(fact[MX]);
    for(int i = MX - 1; i >= 0; i--){
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

ll nCr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

ll nPr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[n - r] % MOD;
}typedef long long ll;
const int MOD = 1000000007;
const int MX = 1005;
ll binpow(ll a, ll b, ll m = MOD){
    ll res = 1;
    a %= m;
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll a){
    return binpow(a, MOD - 2, MOD);
}

static ll fact[MX + 1], invfact[MX + 1];
void init_factorials(){
    fact[0] = 1;
    for(int i = 1; i <= MX; i++){
        fact[i] = fact[i - 1] * i % MOD;
    }
    invfact[MX] = inv(fact[MX]);
    for(int i = MX - 1; i >= 0; i--){
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

ll nCr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

ll nPr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[n - r] % MOD;
}
class Solution {
public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        init_factorials();
        int n = nums.size();
        unordered_map<int, int> p, s;
        vector<int> pre(n), suf(n);
        vector<int> up(n), us(n);
        for(int i = 0; i < n; i++){
            up[i] = p.size();
            pre[i] = p[nums[i]];
            p[nums[i]]++;
        }       
        for(int i = n - 1; i >= 0; i--){
            us[i] = s.size();
            suf[i] = s[nums[i]];
            s[nums[i]]++;
        }

        ll ans = 0;
        for(int i = 2; i < n - 2; i++){
            if(pre[i] >= 2){
                ans = (ans + nCr(pre[i], 2) * nCr(n - i - 1, 2) % MOD) % MOD;
            }
            else if(suf[i] >= 2){
                ans = (ans + nCr(suf[i], 2) * nCr(i, 2) % MOD) % MOD;
            }
            else if(pre[i] == 1 && suf[i] == 1){
                ans = (ans + (i - 1) * (n - i - 2) % MOD) % MOD;
            }
            else if(pre[i] == 1){
                for(int j = 0; j < i; j++){
                    if(nums[j] == nums[i]) continue;
                    int it = find(nums.begin() + i + 1, nums.end(), nums[j]) - nums.begin();
                    int cnt = 0;
                    if(it != nums.size()){
                        cnt = nCr(us[i] - suf[it] - 1, 2);
                    }
                    else{
                        cnt = nCr(us[i], 2);
                    }
                    ans = (ans + cnt) % MOD;
                }
            }
            else if(suf[i] == 1){
                for(int j = i + 1; j < n; j++){
                    if(nums[j] == nums[i]) continue;
                    int it = find(nums.begin() , nums.begin() + i, nums[j]) - nums.begin();
                    int cnt = 0;
                    if(it != i + 1){
                        cnt = nCr(up[i] - pre[it] - 1, 2);
                    }
                    else{
                        cnt = nCr(up[i], 2);
                    }
                    ans = (ans + cnt) % MOD;
                }
            }
            
        }
        return ans % MOD;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
