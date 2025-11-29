import os
import sys
import glob
import time

# ==========================================
# 配置
# ==========================================
DATA_DIR = "test_data"  # 数据文件夹路径

# 终端颜色代码 (让输出更好看)
class Colors:
    OK = '\033[92m'      # 绿色
    FAIL = '\033[91m'    # 红色
    WARNING = '\033[93m' # 黄色
    RESET = '\033[0m'    # 重置

# ==========================================
# 标准解法 (The Correct Logic)
# 必须保证这里的逻辑是绝对正确的数学公式
# ==========================================
def solve_std(L, R):
    # 1. 有效下界：严格大于 R/2，即 >= (R/2 + 1)
    threshold = (R // 2) + 1
    effective_L = max(L, threshold)
    
    # 如果有效区间为空 (effective_L > R)
    # 根据题意，如果找不到符合条件的偶数，至少可以任选 1 个数
    # if effective_L > R:
        # return 1
    
    # 2. 统计 [effective_L, R] 内的偶数个数
    #    公式：count([1, X]) = floor(X/2)
    #    count([A, B]) = count(B) - count(A-1)
    count_R = R // 2
    count_L_minus_1 = (effective_L - 1) // 2
    ans = count_R - count_L_minus_1
    
    # 3. 答案保底为 1
    return max(1, ans)

# ==========================================
# 校验逻辑
# ==========================================
def check_files():
    # 获取所有 .in 文件并排序 (1.in, 2.in, ... 10.in)
    # 默认排序是字符序 (1, 10, 2)，我们需要数字序
    in_files = glob.glob(os.path.join(DATA_DIR, "*.in"))
    
    if not in_files:
        print(f"{Colors.FAIL}Error: No .in files found in directory '{DATA_DIR}'{Colors.RESET}")
        return

    # 按文件名数字排序
    try:
        in_files.sort(key=lambda x: int(os.path.basename(x).split('.')[0]))
    except ValueError:
        in_files.sort() # 如果文件名不是数字，就按默认排序

    print(f"Found {len(in_files)} test cases in '{DATA_DIR}'. Starting validation...\n")
    
    total_errors = 0
    start_time = time.time()

    for file_path in in_files:
        filename = os.path.basename(file_path)
        out_path = file_path.replace(".in", ".out")

        # 检查 .out 文件是否存在
        if not os.path.exists(out_path):
            print(f"{Colors.WARNING}[MISSING] {filename} found but {filename.replace('.in', '.out')} is missing!{Colors.RESET}")
            total_errors += 1
            continue

        # 读取输入
        try:
            with open(file_path, 'r') as f:
                input_data = f.read().split()
        except Exception as e:
            print(f"{Colors.FAIL}[ERROR] Could not read {filename}: {e}{Colors.RESET}")
            continue

        # 读取输出
        try:
            with open(out_path, 'r') as f:
                output_data = f.read().split()
        except Exception as e:
            print(f"{Colors.FAIL}[ERROR] Could not read {os.path.basename(out_path)}: {e}{Colors.RESET}")
            continue

        # 开始逐个 Case 对拍
        ptr_in = 0
        ptr_out = 0
        
        # 解析 T
        if ptr_in >= len(input_data):
            print(f"{Colors.FAIL}[FORMAT] {filename} is empty!{Colors.RESET}")
            continue
            
        T = int(input_data[ptr_in])
        ptr_in += 1
        
        file_passed = True
        
        for case_idx in range(1, T + 1):
            # 获取 L, R
            if ptr_in + 1 >= len(input_data):
                print(f"{Colors.FAIL}[FORMAT] {filename} unexpected end of input at case {case_idx}{Colors.RESET}")
                file_passed = False
                break
            
            L = int(input_data[ptr_in])
            R = int(input_data[ptr_in+1])
            ptr_in += 2
            
            # 获取 .out 中的答案
            if ptr_out >= len(output_data):
                print(f"{Colors.FAIL}[FORMAT] {filename} unexpected end of output file at case {case_idx}{Colors.RESET}")
                file_passed = False
                break
                
            file_ans = int(output_data[ptr_out])
            ptr_out += 1
            
            # 计算标准答案
            std_ans = solve_std(L, R)
            
            # 比对
            if file_ans != std_ans:
                print(f"{Colors.FAIL}[FAIL] {filename} | Case #{case_idx}{Colors.RESET}")
                print(f"  Input:    L={L}, R={R}")
                print(f"  Expected: {std_ans} (Std Solution)")
                print(f"  Found:    {file_ans} (In File)")
                file_passed = False
                total_errors += 1
                # 如果你想遇到错误就停止，取消下面这行的注释
                # return 

        if file_passed:
            print(f"{Colors.OK}[PASS] {filename} ({T} cases verified){Colors.RESET}")
        else:
            print(f"{Colors.FAIL}[FAIL] {filename} contained errors!{Colors.RESET}")

    elapsed = time.time() - start_time
    print("-" * 40)
    if total_errors == 0:
        print(f"{Colors.OK}SUCCESS! All files match the standard logic.{Colors.RESET}")
    else:
        print(f"{Colors.FAIL}FINISHED with {total_errors} errors.{Colors.RESET}")
    print(f"Time taken: {elapsed:.2f} seconds")

if __name__ == "__main__":
    check_files()