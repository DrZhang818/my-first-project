#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/assign-elements-to-groups-with-constraints/description/
/*
    埃氏筛思想 || 枚举倍数
    题意:
        给定两个数组a和b, 要求对于每个a[i], 在数组中找出第一个能够整除a[i]的数字b[j],
        返回下标j的索引数组。 如果a[i]不存在能够整除它的b[j], 则该位置填写-1
    关键思考:
        容易想到刷表法, 即埃氏筛的思想, 把每个以b[i]为答案的数字全部标记
        注意, 如果一个外层循环的x已经被标记, 一定要跳过, 否则时间复杂度无法降到调和级数级别
*/


//优化解法
class Solution {
public:
    vector<int> assignElements(vector<int>& a, vector<int>& b) {
        const int MX = *max_element(a.begin(), a.end()) + 1;
        vector<int> vis(MX, -1);
        for(int i = 0; i < b.size(); i++) {
            int x = b[i];
            if(x >= MX || vis[x] != -1) continue;
            for(int j = x; j <= MX; j += x) {
                if(vis[i] == -1) {
                    vis[j] = i;
                }
            }
        }
        for(int i = 0; i < a.size(); i++) {
            a[i] = vis[a[i]];
        }
        return a;
    }
};


//nsqrt(n)做法(容易超时)
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int n = groups.size();
        vector<int> ans(n, -1);
        unordered_map<int,int> mp;
        for(int i = 0; i < elements.size(); i++) {
            if(mp.find(elements[i]) != mp.end()) continue;
            mp[elements[i]] = i;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 1; j * j <= groups[i]; j++) {
                if(groups[i] % j == 0) {
                    if(mp.find(j) != mp.end()) {
                        if(ans[i] == -1) {
                            ans[i] = mp[j];
                        } else {
                            ans[i] = min(ans[i], mp[j]);
                        }
                    }
                    if(mp.find(groups[i] / j) != mp.end()) {
                        if(ans[i] == -1) {
                            ans[i] = mp[j];
                        } else {
                            ans[i] = min(ans[i], mp[groups[i] / j]);
                        }
                    }
                }
            }
        }
        return ans;
    }
};