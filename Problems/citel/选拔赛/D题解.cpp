#include <bits/stdc++.h>
using namespace std;

struct Submission {
    int a, b; // time, problem
    string s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    // 全局数据量约束：sum(n), sum(k) <= 2*10^5，需小心内存与效率

    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<Submission>> problems(n+1);
        for (int i = 0; i < k; i++) {
            Submission sub;
            cin >> sub.a >> sub.b >> sub.s;
            problems[sub.b].push_back(sub);
        }

        // 对每题处理
        // 输出信息：
        // 强制通过题计数和罚时总和 A_count, A_sum
        // 可选通过题罚时列表 B
        int A_count = 0;
        long long A_sum = 0;
        vector<long long> optionalPenalties; // B

        for (int p = 1; p <= n; p++) {
            auto &subs = problems[p];
            if (subs.empty()) {
                // 无提交，不可通过
                continue;
            }

            sort(subs.begin(), subs.end(), [](auto &x, auto &y) {
                return x.a < y.a;
            });

            // 找最早 Accepted 的提交
            int earliestAcceptedTime = -1;
            int earliestAcceptedIndex = -1;
            // 找最早 Running 的提交
            int earliestRunningTime = -1;
            int earliestRunningIndex = -1;

            // 统计rejected提交的数量随时间变化
            // 当找到accepted时需要知道之前多少个rejected
            int rejectedCount = 0;

            // 为运行中(Running)的提交做同样统计
            // 但我们需要确定在其之前的rejected数
            vector<int> rejectedBefore; 
            rejectedBefore.reserve((int)subs.size());

            for (int i = 0; i < (int)subs.size(); i++) {
                rejectedBefore.push_back(rejectedCount);
                if (subs[i].s == "Rejected") {
                    rejectedCount++;
                }
            }

            // 重置rejectedCount以便在获取accepted和running时使用
            rejectedCount = 0;
            for (int i = 0; i < (int)subs.size(); i++) {
                if (subs[i].s == "Accepted") {
                    // 找到最早accepted
                    if (earliestAcceptedTime == -1) {
                        earliestAcceptedTime = subs[i].a;
                        earliestAcceptedIndex = i;
                    }
                }
            }

            // 对于running提交，选择最早的一个作为potential accepted candidate
            for (int i = 0; i < (int)subs.size(); i++) {
                if (subs[i].s == "Running") {
                    // running之前的rejected数量 = rejectedBefore[i]
                    // 如果该running变accepted，罚时 = subs[i].a + rejectedBefore[i]*20
                    if (earliestRunningTime == -1) {
                        earliestRunningTime = subs[i].a;
                        earliestRunningIndex = i;
                    } else {
                        // 如果已有更早的running，就不需要考虑后面的，因为后面的罚时只会更大
                    }
                }
            }

            // 计算该题最小的accepted罚时方案
            // 有两种可能：
            // 1) 原生accepted：罚时 = earliestAcceptedTime + (#rejected before that)*20
            // 2) 无原生accepted则看running：罚时 = earliestRunningTime + (#rejected before running)*20

            // 首先计算原生accepted的罚时
            long long forcedPenalty = -1;
            if (earliestAcceptedTime != -1) {
                // earliestAcceptedIndex不为-1
                int rcount = rejectedBefore[earliestAcceptedIndex]; 
                forcedPenalty = earliestAcceptedTime + rcount*20LL;
            }

            // 计算running作为accepted的罚时
            long long runningPenalty = -1;
            if (earliestRunningTime != -1) {
                int rcount = rejectedBefore[earliestRunningIndex]; 
                runningPenalty = earliestRunningTime + rcount*20LL;
            }

            // 如果有原生accepted，则该题强制通过
            if (forcedPenalty != -1) {
                // 无论怎么改running，该题都已被accepted过，无法取消accepted
                A_count++;
                A_sum += forcedPenalty;
            } else {
                // 无原生accepted
                // 如果有runningPenalty，则该题是可选通过题
                if (runningPenalty != -1) {
                    optionalPenalties.push_back(runningPenalty);
                }
                // 如果连runningPenalty都没有，则该题不可通过（只能保持0罚时，不通过）
            }
        }

        // 对可选通过题罚时排序
        sort(optionalPenalties.begin(), optionalPenalties.end());
        // 前缀和
        vector<long long> prefix((int)optionalPenalties.size()+1,0);
        for (int i = 1; i <= (int)optionalPenalties.size(); i++) {
            prefix[i] = prefix[i-1] + optionalPenalties[i-1];
        }

        // 对x=1到n输出结果
        for (int x = 1; x <= n; x++) {
            if (x < A_count) {
                cout << -1 << (x==n?'\n':' ');
            } else {
                int need = x - A_count;
                if (need > (int)optionalPenalties.size()) {
                    cout << -1 << (x==n?'\n':' ');
                } else {
                    cout << A_sum + (need>0?prefix[need]:0) << (x==n?'\n':' ');
                }
            }
        }
    }

    return 0;
}
