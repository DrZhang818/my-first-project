#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <numeric>
#include <iomanip>

using namespace std;

// ================== 全局变量 ==================

int N;
vector<int> row_vals; // 每一行的整数值
map<vector<int>, int> memo; // 记忆化: {r_mask, c_mask, current_xor} -> AliceFinalScore

// 计算二进制中1的个数
int countSetBits(int x) {
    return __builtin_popcount(x);
}

// ================== 矩阵特征辅助函数 ==================

// 计算矩阵在 GF(2) 下的秩
int get_rank(vector<int> mat_rows) {
    int n = mat_rows.size();
    int rank = 0;
    int row = 0;
    // 高斯消元
    for (int c = n - 1; c >= 0 && row < n; --c) {
        int pivot = -1;
        for (int r = row; r < n; ++r) {
            if ((mat_rows[r] >> c) & 1) {
                pivot = r;
                break;
            }
        }
        if (pivot != -1) {
            swap(mat_rows[row], mat_rows[pivot]);
            for (int r = 0; r < n; ++r) {
                if (r != row && ((mat_rows[r] >> c) & 1)) {
                    mat_rows[r] ^= mat_rows[row];
                }
            }
            rank++;
            row++;
        }
    }
    return rank;
}

// ================== 博弈求解核心 (Minimax) ==================

int solve_game(int r_mask, int c_mask, int turn, int current_xor) {
    if (turn > 2 * N - 1) {
        return current_xor;
    }

    vector<int> state = {r_mask, c_mask, current_xor};
    if (memo.count(state)) {
        return memo[state];
    }

    int result;

    if (turn % 2 != 0) { // Alice
        result = 0; 
        for (int r = 0; r < N; ++r) {
            if ((r_mask >> r) & 1) {
                int val = row_vals[r] & c_mask;
                int gain = countSetBits(val) % 2;
                if (solve_game(r_mask ^ (1 << r), c_mask, turn + 1, current_xor ^ gain) == 1) {
                    result = 1;
                    break; 
                }
            }
        }
    } else { // Bob
        result = 1; 
        for (int c = 0; c < N; ++c) {
            if ((c_mask >> c) & 1) {
                if (solve_game(r_mask, c_mask ^ (1 << c), turn + 1, current_xor) == 0) {
                    result = 0;
                    break; 
                }
            }
        }
    }
    return memo[state] = result;
}

// ================== 过滤与输出 ==================

// 检查是否是需要研究的情况
// 返回 true 表示保留，false 表示过滤
bool should_study(const vector<vector<int>>& mat, int& out_c0, int& out_c1) {
    int n = mat.size();
    int c0 = 0;
    int c1 = 0;

    for (const auto& row : mat) {
        int sum = 0;
        int prod = 1;
        for (int x : row) {
            sum += x;
            prod &= x;
        }
        if (sum == 0) c0++;
        if (prod == 1) c1++;
    }
    
    out_c0 = c0;
    out_c1 = c1;

    // 过滤规则 1: 跳过每一行都是混合行的情况 (c0=0 且 c1=0)
    if (c0 == 0 && c1 == 0) return false;

    // 过滤规则 2: 跳过同时存在全0和全1行的情况 (c0>0 且 c1>0)
    if (c0 > 0 && c1 > 0) return false;

    // 保留剩下的情况：
    // A: 只有全0行 + 混合行 (c0 > 0, c1 = 0)
    // B: 只有全1行 + 混合行 (c0 = 0, c1 > 0)
    return true;
}

string get_winner_and_stats(const vector<vector<int>>& mat) {
    N = mat.size();
    row_vals.assign(N, 0);
    int total_xor = 0;
    
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(mat[i][j]) {
                row_vals[i] |= (1 << j);
                total_xor ^= 1;
            }
        }
    }

    if (total_xor == 0) return "Draw";

    memo.clear();
    int init_mask = (1 << N) - 1;
    if (solve_game(init_mask, init_mask, 1, 0) == 1) {
        return "Alice";
    } else {
        return "Bob";
    }
}

// ================== 矩阵生成与去重 ==================

bool is_canonical(const vector<vector<int>>& mat) {
    int n = mat.size();
    vector<int> current_rows;
    for(const auto& row : mat) {
        int val = 0;
        for(int x : row) val = (val << 1) | x;
        current_rows.push_back(val);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    do {
        vector<int> transformed_rows;
        transformed_rows.reserve(n);
        for(int i = 0; i < n; ++i) {
            int val = 0;
            for(int j = 0; j < n; ++j) {
                val = (val << 1) | mat[i][p[j]];
            }
            transformed_rows.push_back(val);
        }
        sort(transformed_rows.begin(), transformed_rows.end());
        if (transformed_rows < current_rows) return false;
    } while (next_permutation(p.begin(), p.end()));

    return true;
}

void print_matrix(const vector<vector<int>>& mat, const string& winner, int c0, int c1) {
    cout << "Pattern: [c0=" << c0 << ", c1=" << c1 << "]" << endl;
    cout << "Rank: " << get_rank(row_vals) << endl;
    for(const auto& row : mat) {
        cout << "  ";
        for(int x : row) cout << x << " ";
        cout << endl;
    }
    cout << "Winner: " << winner << endl;
    cout << "----------------------" << endl;
}

void generate_and_solve(int n, int r, vector<vector<int>>& current_mat, int last_row_val) {
    if (r == n) {
        if (is_canonical(current_mat)) {
            int c0, c1;
            if (should_study(current_mat, c0, c1)) {
                string winner = get_winner_and_stats(current_mat);
                if (winner != "Draw") {
                    print_matrix(current_mat, winner, c0, c1);
                }
            }
        }
        return;
    }

    int limit = 1 << n;
    for (int val = last_row_val; val < limit; ++val) {
        for (int c = 0; c < n; ++c) {
            current_mat[r][c] = (val >> (n - 1 - c)) & 1;
        }
        generate_and_solve(n, r + 1, current_mat, val);
    }
}

int main() {
    int n_in;
    cout << "Enter N (3 or 4 recommended): ";
    if (cin >> n_in) {
        vector<vector<int>> mat(n_in, vector<int>(n_in));
        cout << "Searching for unsolved patterns (Filtered)..." << endl;
        cout << "----------------------" << endl;
        generate_and_solve(n_in, 0, mat, 0);
        cout << "Done." << endl;
    }
    return 0;
}