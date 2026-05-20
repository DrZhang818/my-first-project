#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 8E4;

int cnta[N + 1], cntb[N + 1];
int timer = 0;
int Ta[N + 1], Tb[N + 1], Va[N + 1], Vb[N + 1];

class Solution {
public:
    int minCost(vector<int>& a, vector<int>& b) {
        ++timer;
        for(int x : a) {
            if(Ta[x] != timer) {
                Ta[x] = timer;
                cnta[x] = 1;
            } else {
                cnta[x]++;
            }
        }
        for(int x : b) {
            if(Tb[x] != timer) {
                Tb[x] = timer;
                cntb[x] = 1;
            } else {
                cntb[x]++;
            }
        }

        int ans = 0;
        for(int x : a) {
            if(Va[x] == timer) {
                continue;    
            }
            Va[x] = timer;
            if(Tb[x] != timer) {
                Tb[x] = timer;
                cntb[x] = 0;
            }
            if(cnta[x] > cntb[x]) {
                if(cnta[x] - cntb[x] & 1) {
                    return -1;
                }
                ans += cnta[x] - cntb[x] >> 1;
            }
        }
        for(int x : b) {
            if(Vb[x] == timer) continue;
            Vb[x] = timer;
            if(Ta[x] != timer) {
                Ta[x] = timer;
                cnta[x] = 0;
            }
            if(cntb[x] > cnta[x]) {
                if(cntb[x] - cnta[x] & 1) {
                    return -1;
                }
                ans += cntb[x] - cnta[x] >> 1;
            }
        }

        if(ans & 1) {
            return -1;
        }
        return ans / 2;
    }
};