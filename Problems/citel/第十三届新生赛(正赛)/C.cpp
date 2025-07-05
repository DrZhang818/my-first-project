#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    字符串 || 哈希表
    题意: 给定n个字符串, 你的任务是删除每个字符串中的小写字母, 并统计
        删除后格式为"...TXDY"的字符串个数(其中...不能为空)
        返回个数最多的串(只返回...), 如果多个串次数最大且相同, 返回字典序最小的
    只需要模拟题意即可
*/
//优化做法
void solve1(){
    int n;
    cin >> n;
    unordered_map<string, int> count;
    while(n--){
        string s, t;
        cin >> s;
        for(auto c : s){
            if(isupper(c)) t += c;
        }
        if(t.size() >= 5 && t.substr(t.size() - 4, 4) == "TXDY"){
            count[t.substr(0, t.size() - 4)]++;
        }
    }
    string ans;
    int maxCnt = 0;
    for(auto &[s, cnt] : count){
        if(cnt > maxCnt || cnt == maxCnt && s < ans){
            ans = s;
            maxCnt = cnt;
        }
    }
    cout << ans << "\n";
}
//比赛时做法
void solve(){
    int n;
    cin >> n;
    cin.ignore();
    unordered_map<string, int> count;

    for (int i = 0; i < n; i++) {
        string s, t;
        getline(cin, t);

        for (int j = 0; j < t.size(); j++) {
            if (t[j] >= 'A' && t[j] <= 'Z') {
                s += t[j];
            }
        }
        string tt;
        if (s.size() < 4) {
            continue;
        }
        for (int k = s.size() - 4; k < s.size(); k++) {
            tt += s[k];
        }
        if (tt == "TXDY") {
            string res = s.substr(0, s.size() - 4);
            if (res == "")
                continue;
            count[res]++;
        }
    }
    int ans = 0;
    string anss;
    for (auto it = count.begin(); it != count.end(); it++) {

        string ss = it->first;
        int cnt = it->second;
        
        if (cnt >= ans) {
            if (cnt > ans) {
                ans = cnt;
                anss = ss;
            } else {
                ans = cnt;
                anss = min(anss, ss);
            }
        }
    }
    cout << anss << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}