#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://ac.nowcoder.com/acm/contest/96366/I
/*
    有重复元素的回溯 || 字符串分割
*/
int compute(string &s){
    int ans = 1;
    string t;
    vector<int> nums;
    for(int i = s.length() - 1; i >= 0; i--){
        t += s[i];
        if(t.length() == 3 || i == 0){
            reverse(t.begin(), t.end());
            nums.push_back(stoi(t));
            t.clear();
        }
    }
    for(auto num : nums){
        ans *= num;
    }
    return ans;
}
void solve(){
    string s;
    cin >> s;
    int ans = 0;
    auto dfs = [&](auto&& dfs, int i) -> void{
        if(i == s.length() - 1){
            ans = max(ans, compute(s));
            return;
        }
        for(int j = i; j < s.length(); j++){
            swap(s[i], s[j]);
            dfs(dfs, i + 1);
            swap(s[i], s[j]);
        }
    };
    dfs(dfs, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    return 0;
}