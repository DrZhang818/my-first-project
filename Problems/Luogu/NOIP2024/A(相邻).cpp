#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.luogu.com.cn/problem/P11361
/*
    贪心思维 || 并查集 || 图论 || 字符串
    题意: 给定两个二进制字符串, 每个字符串被分割成了若干个连通块, 连通块内字符可以
          任意调整顺序。 求两个字符串的最长公共子序列的长度
    关键思考:
        从左往右贪心, 考虑当前位置在可以相同的情况下是否一定要相同?
            假如可以相同但我们不让他相同, 那么此处的贡献就是-1, 而省出来的字符在后面
        最多造成1的贡献, 也就是这种方案的贡献<=0, 一定不是最优解
        因此, 贪心策略就是能相同就相同, 只需要分成可以相同/不可以相同两类即可
    关键部分:
        利用并查集把每个位置属于的连通块预处理
*/

void solve(){
    int n;
    cin >> n;
    string s1, s2, t1, t2;
    cin >> s1 >> s2 >> t1 >> t2;
    vector<int> set1(n), set2(n);
    for(int i = 1; i < n; i++){
        set1[i] = (t1[i] == '1' && t1[i - 1] == '1') ? set1[i - 1] : i;
        set2[i] = (t2[i] == '1' && t2[i - 1] == '1') ? set2[i - 1] : i; 
    }
    vector<PII> cnt1(n), cnt2(n);
    for(int i = 0; i < n; i++){ 
        s1[i] == '1' ? cnt1[set1[i]].first++ : cnt1[set1[i]].second++;
        s2[i] == '1' ? cnt2[set2[i]].first++ : cnt2[set2[i]].second++;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(cnt1[set1[i]].first > 0 && cnt2[set2[i]].first > 0){
            ans++;
            cnt1[set1[i]].first--;
            cnt2[set2[i]].first--;
        }
        else if(cnt1[set1[i]].second > 0 && cnt2[set2[i]].second > 0){
            ans++;
            cnt1[set1[i]].second--;
            cnt2[set2[i]].second--;
        }
        else if(cnt1[set1[i]].first > 0){
            cnt1[set1[i]].first--;
            cnt2[set2[i]].second--;
        }
        else{
            cnt1[set1[i]].second--;
            cnt2[set2[i]].first--;
        }
    }
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