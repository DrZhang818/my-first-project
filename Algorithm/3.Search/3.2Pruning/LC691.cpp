#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/stickers-to-spell-word/
/*
    题意:
        给定一个长度为n的字符串数组ss, 表示有n种不同的贴纸, 以及一个目标单词t
        对于每张贴纸, 你都可以通过切割的方式获得贴纸所包含的所有字符
        每种贴纸的数量是无限的
        要求计算出组成目标单词t所需要的最小贴纸数量
    关键思考:
        本质来说是个多重集合覆盖问题, 我们要通过选若干个子集, 覆盖单词t的集合
        可以把问题建模为多重完全背包问题, 但由于维度过大, 我们需要进行剪枝
        这里最核心的剪枝方法是等效冗余剪枝 + 记忆化剪枝
        我们可以把t排序
        然后定义f(t) := 覆盖t所需的最小数量
        那么比较显然的状态转移是:
        枚举ss中的每个集合s, 计算选择s后剩余的集合(t-s)所需的最小数量
        即: f(t) = 1 + min(f(t-si)) (i∈[1,n]), 这里的-代表差集
        这里我们做个思考: 假设要覆盖的是aaabbc
        假设一种合法方案是1123...
        那么显然地1321.../2131.../...都是合法方案
        所以这里涉及到一个记忆化剪枝, 计算完1123后, 再计算1321.../2131.../...时就可以利用记忆化的结果
        但这还不够, 仍然有大量冗余搜索
        我们按照当前要解决的字符串的第一个字符来分类
        当前aaabbc, 第一个字符是a
        那么我们在枚举ss中的集合的时候, 就可以把集合分成"包含a"和"不包含a"
        当我们搜索完"包含a"的所有情况后, "不包含a"的就可以全部舍弃了
        因为早晚都要选"包含a"的集合, 意味着选择"包含a"这一次操作在"不包含a"的后续操作中必然进行
        那么贪心地想, 这一次选择"包含a"一定是正贡献, 而选择"不包含a"的贡献可正可0
        通过分析, 我们发现选择"包含a"一定比选择"不包含a"更优
        因此最优解一定存在于"包含a"的分支中(即使不包含a的分支也可能有, 但我们可以排除等效冗余)
        所以我们可以跑一遍记忆化dfs + 等效冗余剪枝

        另一个方法是使用bfs, 因为bfs天然适合求这种等权最短路, 并且bfs就不涉及到记忆化剪枝了
        只要做好去重 + 等效冗余剪枝, 保证队列不爆炸就可以了
*/
//BFS
class Solution {
public:
    int minStickers(vector<string>& ss, string t) {
        int n = ss.size();
        vector<vector<int>> cnt(n, vector<int>(26, 0));
        for(int i = 0; i < n; i++) {
            for(char c : ss[i]) {
                cnt[i][c - 'a'] += 1;
            }
        }
        sort(t.begin(), t.end());
        //set用于去重
        unordered_set<string> st;
        st.insert(t);

        queue<string> q;
        q.push(t);
        int ans = 0;
        while(!q.empty()) {
            int len = q.size();
            for(int i = 0; i < len; i++) {
                string cur = q.front();
                q.pop();
                if(cur.empty()) {
                    return ans;
                }
                vector<int> cur_cnt(26, 0);
                for(auto c : cur) {
                    cur_cnt[c - 'a'] += 1;
                }
                for(int j = 0; j < n; j++) {
                    //等效冗余剪枝
                    if(cnt[j][cur[0] - 'a'] == 0) continue;
                    string ns;
                    for(int k = 0; k < 26; k++) {
                        ns.append(max(cur_cnt[k] - cnt[j][k], 0), k + 'a');
                    }
                    //去重
                    if(!st.count(ns)) {
                        st.insert(ns);
                        q.push(ns);
                    }
                }
            }
            ans += 1;
        }
        return -1;
    }
};
//DFS
class Solution1 {
public:
    int minStickers(vector<string>& ss, string t) {
        int n = ss.size();
        vector<vector<int>> cnt(n, vector<int>(26));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < ss[i].size(); j++) {
                cnt[i][ss[i][j] - 'a'] += 1;
            }
        }
        sort(t.begin(), t.end());
        unordered_map<string, int> mp;
        mp[""] = 0;
        int ans = 0;
        auto dfs = [&](this auto &&dfs, string cur) -> int {
            if(mp.find(cur) != mp.end()) return mp[cur];
            vector<int> need(26);
            for(auto c : cur) {
                need[c - 'a'] += 1;
            }
            int res = INT_MAX / 2;
            for(int i = 0; i < n; i++) {
                if(cnt[i][cur[0] - 'a'] == 0) continue;
                string ns;
                for(int j = 0; j < 26; j++) {
                    ns.append(max(0, need[j] - cnt[i][j]), j + 'a');
                }
                res = min(res, 1 + dfs(ns));
            }
            return mp[cur] = res;
        };
        ans = dfs(t);
        return ans >= INT_MAX / 2 ? -1 : ans;
    }
};