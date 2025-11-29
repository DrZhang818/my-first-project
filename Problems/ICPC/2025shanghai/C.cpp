#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 全局变量存储当前排列和操作记录
int n;
vector<int> p;
struct Op {
    int l, r;
};
vector<Op> ops;

// 检查当前排列是否有序
bool is_sorted_perm() {
    for (int i = 1; i <= n; ++i) {
        if (p[i] != i) return false;
    }
    return true;
}

// 执行 FakeSort 操作
// 返回值：如果排列发生了改变，返回 true；否则返回 false
bool do_op(int l, int r) {
    // 边界检查及偶数长度检查
    if (l < 1 || r > n || l >= r) return false;
    if ((r - l + 1) % 2 != 0) return false;

    int k = r - l + 1;
    int half = k / 2;

    // 1. 提取区间内的元素
    vector<int> sub(k);
    for (int i = 0; i < k; ++i) sub[i] = p[l + i];
    
    // 2. 对副本排序，用于确定哪些是“小数”，哪些是“大数”
    vector<int> sorted_sub = sub;
    sort(sorted_sub.begin(), sorted_sub.end());

    // 使用 bool 数组标记数值是否属于“较小的一半”
    // 注意：n 最大 10^5，vector<bool> 开销很小
    static vector<bool> is_small;
    if (is_small.size() <= n) is_small.resize(n + 1);
    // 重置标记（只重置用到的部分可能更快，但这里直接重置也不慢）
    // 为了效率，我们只标记当前区间内的数
    // 更优写法：直接用 map 或在 sorted_sub 中二分查找，但 bool 标记最快
    // 这里因为涉及多次调用，需注意清理。
    // 实际上，因为 sub 中元素明确，我们可以只标记 sorted_sub 前 half 个元素
    for (int x : sub) is_small[x] = false; 
    for (int i = 0; i < half; ++i) is_small[sorted_sub[i]] = true;

    // 3. 分离“小数位置”和“大数位置”，以及对应的值
    vector<int> s_vals, l_vals; // 存储值
    vector<int> s_idxs, l_idxs; // 存储下标

    for (int i = 0; i < k; ++i) {
        int val = p[l + i];
        int idx = l + i;
        if (is_small[val]) {
            s_vals.push_back(val);
            s_idxs.push_back(idx);
        } else {
            l_vals.push_back(val);
            l_idxs.push_back(idx);
        }
    }

    // 4. 对值进行排序（题目要求：内部按升序排列）
    sort(s_vals.begin(), s_vals.end());
    sort(l_vals.begin(), l_vals.end());

    // 5. 将排好序的值放回对应的位置
    bool changed = false;
    for (int i = 0; i < s_vals.size(); ++i) {
        if (p[s_idxs[i]] != s_vals[i]) {
            p[s_idxs[i]] = s_vals[i];
            changed = true;
        }
    }
    for (int i = 0; i < l_vals.size(); ++i) {
        if (p[l_idxs[i]] != l_vals[i]) {
            p[l_idxs[i]] = l_vals[i];
            changed = true;
        }
    }

    // 6. 记录操作
    if (changed) {
        ops.push_back({l, r});
    }
    return changed;
}

void solve() {
    cin >> n;
    p.resize(n + 1);
    // 优化：重置 is_small 数组大小以防越界，虽在 do_op 中处理，这只是习惯
    for (int i = 1; i <= n; ++i) cin >> p[i];

    ops.clear();
    
    // 策略：循环应用一组能覆盖不同位置混合的操作
    // 循环次数设定为 25 次，每次循环最多 4 个操作，总共不超过 100 次，满足 <= 114 的限制。
    for (int iter = 0; iter < 25; ++iter) {
        if (is_sorted_perm()) break;
        
        // 1. 全局排序
        bool c1 = do_op(1, n);
        if (is_sorted_perm()) break;
        
        // 2. 中间混合 (长度 n-2，需 n >= 4)
        bool c2 = false;
        if (n >= 4) c2 = do_op(2, n - 1);
        if (is_sorted_perm()) break;
        
        // 3. 左偏混合 (长度 n-2，需 n >= 4)
        bool c3 = false;
        if (n >= 4) c3 = do_op(1, n - 2);
        if (is_sorted_perm()) break;
        
        // 4. 右偏混合 (长度 n-2，需 n >= 4)
        bool c4 = false;
        if (n >= 4) c4 = do_op(3, n);
        if (is_sorted_perm()) break;
        
        // 优化：如果一整轮操作都没有改变数组，说明陷入死锁，无需继续
        if (!c1 && !c2 && !c3 && !c4) break;
    }

    if (is_sorted_perm()) {
        cout << ops.size() << "\n";
        for (auto& op : ops) {
            cout << op.l << " " << op.r << "\n";
        }
    } else {
        cout << "-1\n";
    }
}

int main() {
    // IO 优化
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}