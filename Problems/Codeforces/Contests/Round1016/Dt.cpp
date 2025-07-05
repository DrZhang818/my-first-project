#include <iostream>
#include <string>
#include <vector>

// 使用 long long 来存储坐标和数值，因为它们可能很大
using ll = long long;

// 存储坐标的结构体
struct Coords {
    ll x, y;
};

/**
 * @brief 递归计算在 n 级 (2^n x 2^n) 表格中，坐标 (x, y) 处的数字。
 *
 * @param n 表格的级别 (大小为 2^n x 2^n)。
 * @param x 行坐标 (1-based)。
 * @param y 列坐标 (1-based)。
 * @return ll 坐标 (x, y) 处的数字。
 */
ll getNumber(int n, ll x, ll y) {
    // 基本情况：n=1，即 2x2 表格
    if (n == 1) {
        if (x == 1 && y == 1) return 1; // 左上
        if (x == 2 && y == 2) return 2; // 右下
        if (x == 2 && y == 1) return 3; // 左下
        if (x == 1 && y == 2) return 4; // 右上
    }

    // 计算子表格的大小 (2^(n-1))
    ll subSize = 1LL << (n - 1);
    // 计算每个子表格包含的数字数量 ( (2^(n-1))^2 = 2^(2n-2) )
    ll subCount = subSize * subSize;

    // 判断 (x, y) 属于哪个子表格 (象限)
    if (x <= subSize && y <= subSize) {
        // 1. 左上象限：直接递归计算子问题
        return getNumber(n - 1, x, y);
    } else if (x > subSize && y > subSize) {
        // 2. 右下象限：数字在前一个子表格之后，加上 subCount
        //    坐标需要相对于子表格进行调整 (x - subSize, y - subSize)
        return getNumber(n - 1, x - subSize, y - subSize) + subCount;
    } else if (x > subSize && y <= subSize) {
        // 3. 左下象限：数字在前两个子表格之后，加上 2 * subCount
        //    坐标需要相对于子表格进行调整 (x - subSize, y)
        return getNumber(n - 1, x - subSize, y) + 2 * subCount;
    } else { // (x <= subSize && y > subSize)
        // 4. 右上象限：数字在前三个子表格之后，加上 3 * subCount
        //    坐标需要相对于子表格进行调整 (x, y - subSize)
        return getNumber(n - 1, x, y - subSize) + 3 * subCount;
    }
}

/**
 * @brief 递归计算数字 d 在 n 级 (2^n x 2^n) 表格中的坐标 (x, y)。
 *
 * @param n 表格的级别 (大小为 2^n x 2^n)。
 * @param d 要查找坐标的数字 (1-based)。
 * @return Coords 包含数字 d 的坐标 {x, y}。
 */
Coords getCoords(int n, ll d) {
    // 基本情况：n=1，即 2x2 表格
    if (n == 1) {
        if (d == 1) return {1, 1}; // 左上
        if (d == 2) return {2, 2}; // 右下
        if (d == 3) return {2, 1}; // 左下
        if (d == 4) return {1, 2}; // 右上
    }

    // 计算子表格的大小 (2^(n-1))
    ll subSize = 1LL << (n - 1);
    // 计算每个子表格包含的数字数量 (2^(2n-2))
    ll subCount = subSize * subSize;

    // 判断数字 d 属于哪个子表格 (象限)
    if (d <= subCount) {
        // 1. 左上象限：直接递归计算子问题，坐标不变
        return getCoords(n - 1, d);
    } else if (d <= 2 * subCount) {
        // 2. 右下象限：在子问题中查找 d - subCount
        //    得到的子坐标 (subX, subY) 需要加上偏移量 (subSize, subSize)
        Coords subCoords = getCoords(n - 1, d - subCount);
        return {subCoords.x + subSize, subCoords.y + subSize};
    } else if (d <= 3 * subCount) {
        // 3. 左下象限：在子问题中查找 d - 2 * subCount
        //    得到的子坐标 (subX, subY) 需要加上行偏移量 subSize
        Coords subCoords = getCoords(n - 1, d - 2 * subCount);
        return {subCoords.x + subSize, subCoords.y};
    } else { // (d <= 4 * subCount)
        // 4. 右上象限：在子问题中查找 d - 3 * subCount
        //    得到的子坐标 (subX, subY) 需要加上列偏移量 subSize
        Coords subCoords = getCoords(n - 1, d - 3 * subCount);
        return {subCoords.x, subCoords.y + subSize};
    }
}

int main() {
    // 加速 C++ 输入输出
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // 测试用例数量
    std::cin >> t;
    while (t--) {
        int n; // 表格级别
        int q; // 查询数量
        std::cin >> n >> q;
        for (int i = 0; i < q; ++i) {
            char type1, type2; // 用于读取查询类型符号 '->' 或 '<-'
            std::cin >> type1 >> type2;

            if (type1 == '-') { // 查询类型: -> x y (找数字)
                ll x, y;
                std::cin >> x >> y;
                // 调用 getNumber 函数并输出结果
                std::cout << getNumber(n, x, y) << "\n";
            } else { // 查询类型: <- d (找坐标)
                ll d;
                std::cin >> d;
                // 调用 getCoords 函数
                Coords result = getCoords(n, d);
                // 输出结果坐标
                std::cout << result.x << " " << result.y << "\n";
            }
        }
    }
    return 0;
}
