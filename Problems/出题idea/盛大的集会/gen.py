import random
import os
import shutil

# ==========================================
# 配置参数
# ==========================================
OUTPUT_DIR = "test_data"  # 输出文件夹名称
TOTAL_FILES = 50          # 生成文件总数
MAX_VAL = 10**18          # 数据上限

# ==========================================
# 标准解法 (用于生成 .out)
# ==========================================
def solve(L, R):
    """
    题目正解：选择 [L, R] 范围内所有 > R/2 的偶数。
    """
    # 1. 有效下界：严格大于 R/2 且 >= L
    #    整数除法 R/2 向下取整，所以 > R/2 等价于 >= (R/2 + 1)
    threshold = (R // 2) + 1
    effective_L = max(L, threshold)
    
    # 如果有效区间为空 (effective_L > R)
    if effective_L > R:
        return 1
    
    # 2. 统计 [effective_L, R] 内的偶数个数
    #    [1, X] 内偶数个数 = floor(X/2)
    count_R = R // 2
    count_L_minus_1 = (effective_L - 1) // 2
    ans = count_R - count_L_minus_1
    
    # 3. 保底为 1
    return max(1, ans)

# ==========================================
# 数据生成策略函数
# ==========================================

def get_random_case(max_r):
    """完全随机"""
    R = random.randint(1, max_r)
    L = random.randint(1, R)
    return L, R

def get_corner_case(max_r):
    """边界情况：L=1, L=R, R-L很小"""
    type_ = random.random()
    if type_ < 0.3:
        # L = R
        R = random.randint(1, max_r)
        return R, R
    elif type_ < 0.5:
        # L = 1
        R = random.randint(1, max_r)
        return 1, R
    elif type_ < 0.8:
        # 极小区间
        R = random.randint(10, max_r)
        diff = random.randint(1, 5)
        L = max(1, R - diff)
        return L, R
    else:
        # R 是 2 的幂次附近
        p = random.randint(1, 60)
        R = 2**p
        if R > max_r: R = max_r
        L = random.randint(1, R)
        return L, R

def get_threshold_case(max_r):
    """核心卡点：L 在 R/2 附近"""
    R = random.randint(100, max_r)
    mid = R // 2
    # 让 L 在 R/2 左右波动 (-100 到 +100)
    offset = random.randint(-100, 100)
    L = mid + offset
    L = max(1, L)
    L = min(L, R)
    return L, R

def get_tiny_interval_large_val(max_r):
    """数值极大，但区间长度很短"""
    R = random.randint(max_r // 2, max_r)
    length = random.randint(0, 200)
    L = max(1, R - length)
    return L, R

# ==========================================
# 主生成流程
# ==========================================
def main():
    # 1. 准备目录
    if os.path.exists(OUTPUT_DIR):
        shutil.rmtree(OUTPUT_DIR)
    os.makedirs(OUTPUT_DIR)
    
    print(f"Generating {TOTAL_FILES} sets of test data in '{OUTPUT_DIR}/'...")

    for file_id in range(1, TOTAL_FILES + 1):
        cases = []
        
        # ==================================
        # 难度梯度控制
        # ==================================
        if file_id <= 5:
            # [1-5]: 极小数据，用于手算验证
            T = 10
            for _ in range(T):
                cases.append(get_random_case(100))
                
        elif file_id <= 10:
            # [6-10]: 边界测试 (L=R, L=1等)
            T = 20
            for _ in range(T):
                cases.append(get_corner_case(1000))
                
        elif file_id <= 20:
            # [11-20]: 中等规模随机 (1e9)
            T = 100
            for _ in range(T):
                cases.append(get_random_case(10**9))
                
        elif file_id <= 30:
            # [21-30]: 核心卡点 (针对贪心策略的攻击数据)
            # L 就在 R/2 附近，这会让 count 发生剧烈变化
            T = 1000
            for _ in range(T):
                cases.append(get_threshold_case(MAX_VAL))
                
        elif file_id <= 45:
            # [31-45]: 极限随机 (1e18)
            T = 1000
            for _ in range(T):
                cases.append(get_random_case(MAX_VAL))
                
        else:
            # [46-50]: 极大数值 + 极短区间
            T = 2000
            for _ in range(T):
                cases.append(get_tiny_interval_large_val(MAX_VAL))

        # ==================================
        # 写入文件
        # ==================================
        file_in_path = os.path.join(OUTPUT_DIR, f"{file_id}.in")
        file_out_path = os.path.join(OUTPUT_DIR, f"{file_id}.out")
        
        # 写入 .in
        with open(file_in_path, 'w') as fin:
            fin.write(f"{len(cases)}\n")
            for L, R in cases:
                fin.write(f"{L} {R}\n")
        
        # 写入 .out
        with open(file_out_path, 'w') as fout:
            for L, R in cases:
                ans = solve(L, R)
                fout.write(f"{ans}\n")
        
        print(f"  Generated {file_id}.in / {file_id}.out (T={len(cases)})")

    print(f"\nDone! All files are in {os.path.abspath(OUTPUT_DIR)}")

if __name__ == "__main__":
    main()