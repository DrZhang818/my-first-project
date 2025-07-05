#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855075520556
/*
    通配符模板匹配问题
    动态规划 || 贪心
*/

/*做法1: 贪心
        假设有两组匹配的token, 那么选前一个一定是更优的
        因此可以对title从左到右进行线性查找
        当且仅当所有token全部找到, 且首尾合法, 结果为True
*/
string solution(int n, string template_, vector<string> titles) {
    vector<string> tokens;
    int len = template_.length();
    string path = "";
    bool ok = true;
    for(int i = 0; i < len; i++){
        char& c = template_[i];
        if(c == '{'){
            tokens.emplace_back(path);
            path.clear();
            ok = false;
        }else if(c == '}'){
            ok = true;
        }else if(ok){
            path += c;
        }
        if(i == len - 1 && ok){
            tokens.emplace_back(path);
            path.clear();
        }
    }
    
    string ans;

    for(auto& s : titles){
        if(template_[0] != '{' && template_[0] != s[0] || template_.back() != '}' && template_.back() != s.back()){
            ans += "False,";
            continue;
        }
        size_t pos = 0;
        int cnt = 0;
        for(auto& token : tokens){
            pos = s.find(token, pos);
            if(pos == string::npos){
                ans += "False,";
                break;
            }else{
                cnt++;
            }
        }
        if(cnt == tokens.size()){
            ans += "True,";
        }
    }
    ans.pop_back();
    return ans;
}
/*
    做法2: 动态规划
    dp[i][j] := pattern的前i个字符能否匹配title的前j个字符
    初始状态: dp[0][0] = true (空模板匹配空标题)
             dp[i][0] = dp[i - 1][0] if pattern[i - 1] == '*' else false
    
    状态转移:
            普通字符：
                    dp[i][j] = dp[i - 1][j - 1], if match
                    dp[i][j] = false,               not match
            通配符:
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j]
*/
string parseTemplate(const string& template_){
    string pattern = "";
    int n = template_.length();
    for(int i = 0; i < n; ){
        if(template_[i] == '{'){
            pattern += '*';
            while(i < n && template_[i] != '}'){
                i++;
            }
            if(i < n && template_[i] == '}'){
                i++;
            }
        }
        else{
            pattern += template_[i];
            i++;
        }
    }
}
bool isMatch(const string& pattern, const string& title){
    int m = pattern.length();
    int n = title.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;
    for(int i = 1; i <= m; i++){
        if(pattern[i - 1] == '*'){
            dp[i][0] = dp[i - 1][0];
        }
        else{
            break;
        }
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(pattern[i - 1] == '*'){
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
            else{
                if(pattern[i - 1] == title[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else{
                    dp[i][j] = false;
                }
            }
        }
    }
    return dp[m][n];
}

//滚动数组优化dp
bool isMatch2(const string& pattern, const string& title){
    int m = pattern.length();
    int n = title.length();
    vector<bool> pre(n + 1, false);
    vector<bool> cur(n + 1, false);

    pre[0] = true;
    for(int i = 1; i <= m; i++){
        if(pattern[i - 1] == '*'){
            cur[0] = pre[0];
        }
        else{
            cur[0] = false;
        }
        for(int j = 1; j <= n; j++){
            if(pattern[i - 1] == '*'){
                cur[j] = pre[j] || cur[j - 1];
            }
            else{
                if(pattern[i - 1] == title[j - 1]){
                    cur[j] = pre[j - 1];
                }
                else{
                    cur[j] = false;
                }
            }
        }
        pre = cur;
    }
    return pre[n];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    string template_;
    cin >> ws // 吃掉前导空白
    getline(cin, template_);
    vector<string> titles(n);
    for(int i = 0; i < n; i++){
        getline(cin, title[i]);
    }
    string pattern = parseTemplate(template_);
    vector<string> results;
    for(int i = 0; i < n; i++){
        bool matchResult = isMatch(pattern, titles[i]);
        if(matchResult){
            results.push_back("True");
        }
        else{
            results.push_back("False");
        }
    }

    for(int i = 0; i < results.size(); i++){
        cout << results[i];
        if(i != results.size() - 1){
            cout << ',';
        }
    }
    cout << '\n';
    return 0;
}




