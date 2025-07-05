#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.luogu.com.cn/problem/P3375
/*
    KMP板子题
    首先计算LPS数组(最长前缀后缀数组)
        方法是利用动态规划
        初始状态: lps[0:] = 0
                初始化cur = 0表示第i个字符接下来与cur作比较
        状态转移: if s[i] == s[cur]
                    lps[i] = ++cur(cur + 1表示长度)
                else
                    cur = lps[cur - 1]
*/
vector<int> getLPS(string& s){
    int n = s.size();
    vector<int> lps(n, 0);
    int cur = 0;
    for(int i = 1; i < n; i++){
        while(cur > 0 && s[i] != s[cur]){
            cur = lps[cur - 1];
        }
        if(s[i] == s[cur]){
            cur++;
            lps[i] = cur;
        }
    }
    return lps;
}

vector<int> KMP(string& s, string& t){
    int n = s.size(), m = t.size();
    vector<int> lps = getLPS(t), pos;
    int j = 0;
    for(int i = 0; i < n; i++){
        while(j > 0 && s[i] != t[j]){
            j = lps[j - 1];
        }
        if(s[i] == t[j]){
            j++;
            if(j == m){
                pos.push_back(i - m + 1);
                j = lps[j - 1];
            }
        }
    }
    return pos;
}
void solve(){
    string s, t;
    cin >> s >> t;
    vector<int> pos = KMP(s, t);
    vector<int> lps = getLPS(t);
    for(auto num : pos){
        cout << num + 1 << "\n";
    }
    for(auto num : lps){
        cout << num << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
