#include <iostream> // 用于输入/输出操作 (cin, cout)
#include <vector>   // 用于使用动态数组 (vector)
#include <string>   // 用于使用字符串操作 (这里不是必须的，但包含进来是好习惯)
#include <numeric>  // 用于可能的数值操作 (当前未使用)
#include <algorithm> // 用于使用算法如 max, min, swap
#include <utility>  // 用于使用 pair

using namespace std;

// 定义结构体存储单局比赛的得分和属性
struct SetScore {
    long long a_pts; // A队在本局的得分
    long long b_pts; // B队在本局的得分
    bool a_wins; // A队是否赢了这局 (基于初始的最小分配)
    bool is_5th; // 这是否是决胜局 (第五局)
};

// 辅助函数，用于计算给定局分x:y所需的:
// - A队和B队的最低总得分 (min_a, min_b)
// - A队在B队获胜局中无需延长规则可得的最高分 (max_non_ext_a)
// - B队在A队获胜局中无需延长规则可得的最高分 (max_non_ext_b)
void calculate_params(int x, int y, long long& min_a, long long& min_b, long long& max_non_ext_a, long long& max_non_ext_b) {
    int n = x + y; // 总局数
    bool is_5th = (n == 5); // 是否有第五局
    // 判断A或B是否赢得决胜局 (仅当n=5时相关)
    bool a_wins_5th = is_5th && (x == 3);
    bool b_wins_5th = is_5th && (y == 3);

    // 计算 min_a (A队赢得x局所需的最低分)
    if (x == 0) {
        min_a = 0;
    } else if (a_wins_5th) { // 如果A赢得第五局，该局只需15分
        min_a = (long long)(x - 1) * 25 + 15;
    } else { // 否则，A队每赢一局需要25分
        min_a = (long long)x * 25;
    }

    // 计算 min_b (B队赢得y局所需的最低分) - 与min_a对称
    if (y == 0) {
        min_b = 0;
    } else if (b_wins_5th) {
        min_b = (long long)(y - 1) * 25 + 15;
    } else {
        min_b = (long long)y * 25;
    }

    // 计算 max_non_ext_a (A队在B队获胜的y局中，在不触发延长规则的情况下能得到的最高分)
    // 在B队获胜的局中(例如 p:25), A队最多得23分(第五局13分)而无需延长
    if (y == 0) {
        max_non_ext_a = 0;
    } else if (b_wins_5th) { // 如果B赢得第五局(p:15), A最多得13分. 其他B赢的y-1局(p:25), A最多得23分.
        max_non_ext_a = (long long)(y - 1) * 23 + 13;
    } else { // B赢得y局(p:25), A在每局中最多得23分.
        max_non_ext_a = (long long)y * 23;
    }

    // 计算 max_non_ext_b (B队在A队获胜的x局中，在不触发延长规则的情况下能得到的最高分) - 与max_non_ext_a对称
    if (x == 0) {
        max_non_ext_b = 0;
    } else if (a_wins_5th) {
        max_non_ext_b = (long long)(x - 1) * 23 + 13;
    } else {
        max_non_ext_b = (long long)x * 23;
    }
}

// 检查函数：判断给定的比赛局分(x:y)在总得分(a_total, b_total)下是否可能实现
bool check(int x, int y, int a_total, int b_total) {
    // 对比赛局分本身进行基本验证
    if (x < 0 || y < 0 || x > 3 || y > 3 || (x < 3 && y < 3) || (x == 3 && y == 3)) {
        return false;
    }

    long long min_a, min_b, max_non_ext_a, max_non_ext_b;
    calculate_params(x, y, min_a, min_b, max_non_ext_a, max_non_ext_b);

    // 检查总得分是否足以达到最低要求
    if (a_total < min_a || b_total < min_b) {
        return false;
    }

    // 计算超出最低要求的“额外”得分
    long long extra_a = a_total - min_a;
    long long extra_b = b_total - min_b;

    // 计算必须通过“赢两分”延长规则得到的点数。
    // ext = max(0, A队超出非延长得分能力所需的分数, B队超出非延长得分能力所需的分数)
    long long ext = max({0LL, extra_a - max_non_ext_a, extra_b - max_non_ext_b});

    // 检查所需延长分数'ext'是否可以通过可用的额外分数实现。
    // 由于延长分数是双方同时+1/+1得到的，我们需要从extra_a中拿出'ext'分，并从extra_b中拿出'ext'分。
    // 因此，ext必须小于或等于extra_a和extra_b。
    return ext <= extra_a && ext <= extra_b;
}

// 构造函数：为一个可能的比赛结果构建并打印一个有效的每局得分序列
void construct(int x, int y, int a_total, int b_total) {
    int n = x + y; // 总局数
    vector<SetScore> sets(n); // 存储每局得分的vector
    int current_x = 0; // 已分配给A的局数计数器
    int current_y = 0; // 已分配给B的局数计数器

    // 重新计算构造所需的参数
    long long min_a, min_b, max_non_ext_a, max_non_ext_b;
    calculate_params(x, y, min_a, min_b, max_non_ext_a, max_non_ext_b);

    // 计算额外得分和所需的延长得分'ext'
    long long extra_a = a_total - min_a;
    long long extra_b = b_total - min_b;
    long long ext = max({0LL, extra_a - max_non_ext_a, extra_b - max_non_ext_b});

    // 计算无需延长规则即可分配的分数
    long long non_ext_a = extra_a - ext;
    long long non_ext_b = extra_b - ext;

    // --- 1. 初始最小得分分配 ---
    // 分配最低获胜分数 (25:0 或 15:0 / 0:25 或 0:15)
    // 暂时将前x局分配给A，后y局分配给B
    for (int i = 0; i < n; ++i) {
        sets[i].is_5th = (i == n - 1) && (n == 5); // 标记是否为第五局
        if (i < x) { // 将前x局分配给A
            sets[i].a_wins = true;
            sets[i].a_pts = sets[i].is_5th ? 15 : 25;
            sets[i].b_pts = 0;
        } else { // 将剩余局分配给B
            sets[i].a_wins = false;
            sets[i].a_pts = 0;
            sets[i].b_pts = sets[i].is_5th ? 15 : 25;
        }
    }

    // --- 2. 纠正第五局获胜者 ---
    // 如果是五局比赛，确保赢得比赛（3局）的队伍被分配赢得第五局。
    // 这很关键，因为第五局的得分规则不同（15分 vs 25分）。
    if (n == 5) {
        bool a_should_win_5th = (x == 3);
        bool b_should_win_5th = (y == 3);
        bool a_is_winning_5th = sets[n - 1].a_wins;

        if (a_should_win_5th && !a_is_winning_5th) {
            // A应赢第五局，但分配给了B。找到一个A赢的非第五局并交换分配。
            for (int i = 0; i < n - 1; ++i) {
                if (sets[i].a_wins) {
                    swap(sets[i].a_wins, sets[n - 1].a_wins); // 交换获胜者标志
                    break;
                }
            }
        } else if (b_should_win_5th && a_is_winning_5th) {
            // B应赢第五局，但分配给了A。找到一个B赢的非第五局并交换分配。
            for (int i = 0; i < n - 1; ++i) {
                if (!sets[i].a_wins) {
                    swap(sets[i].a_wins, sets[n - 1].a_wins); // 交换获胜者标志
                    break;
                }
            }
        }

        // --- 3. 可能的交换后重新初始化分数 ---
        // 基于现在谁赢得第五局，可能需要重新计算分数。
        for (int i = 0; i < n; ++i) {
            sets[i].is_5th = (i == n - 1); // 重新确认第五局状态
            if (sets[i].a_wins) {
                sets[i].a_pts = sets[i].is_5th ? 15 : 25;
                sets[i].b_pts = 0;
            } else {
                sets[i].a_pts = 0;
                sets[i].b_pts = sets[i].is_5th ? 15 : 25;
            }
        }
    }


    // --- 4. 分配非延长分数 ---
    // 将 non_ext_b 分数分配给B队在A队获胜局中的得分
    for (int i = 0; i < n && non_ext_b > 0; ++i) {
        if (sets[i].a_wins) {
            int limit = sets[i].is_5th ? 13 : 23; // B队无需延长可得的最高分
            long long add = min(non_ext_b, (long long)limit);
            sets[i].b_pts += add;
            non_ext_b -= add;
        }
    }

    // 将 non_ext_a 分数分配给A队在B队获胜局中的得分
    for (int i = 0; i < n && non_ext_a > 0; ++i) {
        if (!sets[i].a_wins) {
            int limit = sets[i].is_5th ? 13 : 23; // A队无需延长可得的最高分
            long long add = min(non_ext_a, (long long)limit);
            sets[i].a_pts += add;
            non_ext_a -= add;
        }
    }

    // --- 5. 分配延长分数 ---
    // 添加 'ext' 分数 (需要 "赢两分" 规则)
    // 为简单起见，我们可以将所有 'ext' 分数加到最后一局。
    if (ext > 0) {
        sets[n - 1].a_pts += ext;
        sets[n - 1].b_pts += ext;
    }

    // --- 6. 打印最终每局得分 ---
    for (int i = 0; i < n; ++i) {
        cout << sets[i].a_pts << ":" << sets[i].b_pts << (i == n - 1 ? "" : " ");
    }
    cout << "\n"; // 使用换行符而不是endl，可能输出更快
}


int main() {
    // 优化 C++ 输入/输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m; // 比赛场数
    cin >> m;

    // 定义可能的有效比赛局分，按A队最优顺序排列 (最大化 A胜局 - B胜局)
    vector<pair<int, int>> scores_to_check = {
        {3, 0}, {3, 1}, {3, 2}, {2, 3}, {1, 3}, {0, 3}
    };

    // 处理每场比赛
    while (m--) {
        int a, b; // A队和B队的总得分
        cin >> a >> b;

        bool found = false; // 标记是否找到了有效的局分
        // 按优先顺序遍历可能的局分
        for (const auto& score : scores_to_check) {
            int x = score.first; // A队胜局数
            int y = score.second; // B队胜局数
            // 检查这个局分在给定的总得分下是否可能
            if (check(x, y, a, b)) {
                // 如果可能，打印比赛局分并构造/打印每局得分
                cout << x << ":" << y << "\n";
                construct(x, y, a, b);
                found = true; // 标记为已找到
                break; // 停止检查此比赛的其他局分，因为已找到最优解
            }
        }

        // 如果检查完所有可能性后仍未找到有效局分
        if (!found) {
            cout << "Impossible\n";
        }
    }

    return 0; // 表示程序成功执行
}

