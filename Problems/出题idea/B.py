stand_input, packages = 1, 1
if 1:
    if stand_input:
        import io, os, sys
        input = lambda: sys.stdin.readline().strip()

        import math
        from decimal import Decimal, getcontext
        # 设置 Decimal 精度，防止计算过程中精度丢失
        getcontext().prec = 50
        
        inf = math.inf

        def I():
            return input()
        
        def II():
            return int(input())
        
        def MII():
            return map(int, input().split())

        def LI():
            return input().split()
        
        def LII():
            return list(map(int, input().split()))

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

def solve():
    try:
        # 读取测试用例数量
        line = input()
        if not line: return
        T = int(line)
    except ValueError:
        return

    for _ in range(T):
        try:
            params = LI()
            if not params: break
            TH, TL, VL, T0, V, k, CV, CT = map(int, params)
            
            # 1. 可行性判断
            # 最小需要热水量: VH_min = VL * (T0 - TL) / (TH - T0)
            # 最大可用空间: V_space = V - VL
            # 判断 VH_min <= V_space  =>  VL * (T0 - TL) <= (V - VL) * (TH - T0)
            
            lhs = VL * (T0 - TL)
            rhs = (V - VL) * (TH - T0)
            
            if lhs > rhs:
                print("-1")
                continue
                
            # 2. 计算目标函数斜率指标
            # 目标函数 W 关于 VH 的斜率正负取决于: CV * V - CT * k * (TH - T0)
            slope_metric = CV * V - CT * k * (TH - T0)
            
            if slope_metric > 0:
                # 斜率为正，取最大体积 VH = V - VL，加满水
                # W = CV * V^2 - CT * k * (T_mix - T0) * V
                # 注意 (T_mix - T0) * V = (总热量 - T0 * V)
                # 总热量 = (V - VL) * TH + VL * TL
                
                term1 = CV * V * V
                current_heat = (V - VL) * TH + VL * TL
                target_heat = V * T0
                heat_diff = current_heat - target_heat
                
                term2 = CT * k * heat_diff
                ans = term1 - term2
                # 这种情况结果一定是整数，直接输出
                # 为了格式统一也可以转为浮点字符串
                print(f"{ans}")
                
            else:
                # 斜率为负或0，取最小体积 VH，使得 T_mix = T0
                # 此时等待时间 t_wait = 0
                # W = CV * (VL + VH) * V
                # 代入 VH_min 公式化简得: W = [ CV * V * VL * (TH - TL) ] / (TH - T0)
                
                numerator = CV * V * VL * (TH - TL)
                denominator = TH - T0
                
                # 使用 Decimal 进行高精度除法
                ans = Decimal(numerator) / Decimal(denominator)
                print(f"{ans:.12f}")
                
        except ValueError:
            break

if __name__ == '__main__':
    solve()