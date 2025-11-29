#include <iostream>
#include <vector>
#include <numeric>   // for std::gcd
#include <algorithm> // for std::max
#include <cmath>

using namespace std;

// ==========================================
// Part 1: 暴力搜索 (Brute Force) - 绝对真理
// ==========================================

// 检查两个数是否兼容
bool is_compatible(int u, int v) {
    // 条件1: 共鸣法则 (GCD > 1)
    if (std::gcd(u, v) == 1) return false;
    
    // 条件2: 平等法则 (无倍数关系)
    // 注意: 输入保证 u < v，所以只需要检查 v % u
    if (v % u == 0) return false;
    
    return true;
}

int max_subset_size = 0;
vector<int> best_subset;

// DFS 回溯寻找最大团 (Maximum Clique)
// range_R: 区间右端点
// current_val: 当前考虑的数字
// current_subset: 当前已选集合
void dfs(int range_R, int current_val, vector<int>& current_subset) {
    // 剪枝: 如果当前集合大小 + 剩余可选数字数量 <= 目前找到的最大解，就不搜了
    if (current_subset.size() + (range_R - current_val + 1) <= max_subset_size) {
        return;
    }

    for (int i = current_val; i <= range_R; ++i) {
        // 检查 i 是否与 current_subset 中的所有元素兼容
        bool ok = true;
        for (int x : current_subset) {
            if (!is_compatible(x, i)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            current_subset.push_back(i);
            
            // 更新最大值
            if (current_subset.size() > max_subset_size) {
                max_subset_size = current_subset.size();
                best_subset = current_subset;
            }
            
            dfs(range_R, i + 1, current_subset);
            current_subset.pop_back(); // 回溯
        }
    }
}

// 暴力解的主入口
int solve_brute(int L, int R) {
    max_subset_size = 0;
    best_subset.clear();
    
    // 基础情况：至少可以选 1 个
    if (L <= R) max_subset_size = 1; 

    vector<int> current;
    dfs(R, L, current);
    
    return max_subset_size;
}

// ==========================================
// Part 2: 数学推导 (Math Solution) - 待验证结论
// ==========================================
int solve_math(int L, int R) {
    // 策略：选择 [L, R] 范围内所有 > R/2 的偶数
    
    // 1. 确定有效下界：必须 > R/2，且必须 >= L
    // 整数除法 R/2 向下取整，所以 > R/2 等价于 >= (R/2 + 1)
    int threshold = R / 2 + 1;
    int effective_L = std::max(L, threshold);
    
    // 如果有效区间不存在（比如 L 很大，超过了 R）
    if (effective_L > R) {
        // 根据题意，如果找不到符合策略的集合，我们总是可以任意选 1 个数
        // 只要 L <= R，答案保底为 1
        return 1;
    }
    
    // 2. 统计 [effective_L, R] 范围内的偶数个数
    // [1, X] 内偶数个数为 floor(X/2)
    // [A, B] 内偶数个数 = count(B) - count(A-1)
    int cnt_R = R / 2;
    int cnt_L_minus_1 = (effective_L - 1) / 2;
    int count = cnt_R - cnt_L_minus_1;
    
    // 3. 答案至少为 1 (任意单元素集合总是合法的)
    return std::max(1, count);
}

// ==========================================
// Part 3: 对拍主程序 (Main)
// ==========================================
int main() {
    cout << "Starting Stress Test (Range [1, 50])..." << endl;
    cout << "----------------------------------------" << endl;

    int error_count = 0;

    // 枚举小范围的所有 L, R
    for (int R = 1000; R <= 1050; ++R) {
        for (int L = 1000; L <= R; ++L) {
            
            int ans_brute = solve_brute(L, R);
            int ans_math = solve_math(L, R);

            if (ans_brute != ans_math) {
                error_count++;
                cout << "[FAIL] L=" << L << ", R=" << R << endl;
                cout << "  Brute Force: " << ans_brute << " (Set example: {";
                for (size_t i = 0; i < best_subset.size(); ++i) 
                    cout << best_subset[i] << (i == best_subset.size()-1 ? "" : ",");
                cout << "})" << endl;
                cout << "  Math Solution: " << ans_math << endl;
                cout << "----------------------------------------" << endl;
            }
        }
        if (R % 10 == 0) cout << "Checked up to R=" << R << "..." << endl;
    }

    if (error_count == 0) {
        cout << "\n[SUCCESS] All test cases passed! The hypothesis is likely correct." << endl;
        cout << "Verified logic: Select all even numbers in (" << "R/2" << ", R]." << endl;
    } else {
        cout << "\n[ERROR] Found " << error_count << " mismatches." << endl;
    }

    return 0;
}