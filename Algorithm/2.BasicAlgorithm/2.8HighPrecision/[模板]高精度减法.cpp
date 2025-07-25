#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;

class BigInt {
private:
    // 我们采用 2^32 作为基，每个 unsigned int 存储 32 位数据
    static const unsigned long long BASE = 1ULL << 32;
    // 内部以小端序存储：digits[0] 为低位，digits.back() 为高位
    vector<unsigned int> digits;
    bool negative; // false 表示非负，true 表示负数

    // 去除高位多余的 0
    void trim() {
        while(digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if(digits.size() == 1 && digits[0] == 0)
            negative = false;
    }

    // 比较绝对值大小，返回 -1,0,1 分别表示 a<b, a==b, a>b
    static int compareAbs(const BigInt &a, const BigInt &b) {
        if(a.digits.size() != b.digits.size())
            return a.digits.size() < b.digits.size() ? -1 : 1;
        for (int i = a.digits.size() - 1; i >= 0; i--) {
            if(a.digits[i] != b.digits[i])
                return a.digits[i] < b.digits[i] ? -1 : 1;
        }
        return 0;
    }

    // 绝对值相加（假定两数均为正）
    BigInt addAbs(const BigInt &other) const {
        BigInt res;
        res.digits.clear();
        unsigned long long carry = 0;
        size_t n = max(digits.size(), other.digits.size());
        for (size_t i = 0; i < n || carry; i++) {
            unsigned long long sum = carry;
            if(i < digits.size()) sum += digits[i];
            if(i < other.digits.size()) sum += other.digits[i];
            res.digits.push_back((unsigned int)(sum % BASE));
            carry = sum / BASE;
        }
        res.negative = false;
        res.trim();
        return res;
    }

    // 绝对值相减（假定 *this >= other，且均为正）
    BigInt subAbs(const BigInt &other) const {
        BigInt res;
        res.digits.clear();
        long long carry = 0;
        for (size_t i = 0; i < digits.size(); i++) {
            long long diff = (long long)digits[i] - carry;
            if(i < other.digits.size()) diff -= other.digits[i];
            if(diff < 0) {
                diff += BASE;
                carry = 1;
            } else {
                carry = 0;
            }
            res.digits.push_back((unsigned int)diff);
        }
        res.negative = false;
        res.trim();
        return res;
    }

    // 使用长除法算法计算除法和取余（均按绝对值运算）
    // 返回 <商, 余数>，其中除数为 0 时抛异常
    pair<BigInt, BigInt> divMod(const BigInt &other) const {
        if(other == BigInt(0))
            throw runtime_error("Division by zero");
        // 取绝对值进行运算
        BigInt divisor = other; divisor.negative = false;
        BigInt dividend = *this; dividend.negative = false;
        BigInt quotient;
        quotient.digits.resize(dividend.digits.size(), 0);
        BigInt remainder(0);
        // 处理过程从高位（digits.back()）向低位进行
        for (int i = dividend.digits.size() - 1; i >= 0; i--) {
            // remainder = remainder * BASE
            remainder = remainder << 32;
            // 由于 << 操作已经将低位补 0，这里将新块填入最低位
            remainder.digits[0] = dividend.digits[i];
            remainder.trim();
            // 二分查找求出商的当前位（值在 0 ~ 2^32-1 范围内）
            unsigned int left = 0, right = 0xFFFFFFFF, qdigit = 0;
            while(left <= right) {
                unsigned int mid = left + ((right - left) >> 1);
                BigInt prod = divisor * BigInt(mid);
                if(prod <= remainder) {
                    qdigit = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            quotient.digits[i] = qdigit;
            remainder = remainder - divisor * BigInt(qdigit);
        }
        quotient.negative = (this->negative ^ other.negative);
        quotient.trim();
        remainder.negative = this->negative;
        remainder.trim();
        return {quotient, remainder};
    }

public:
    // 默认构造，表示 0
    BigInt() : negative(false) {
        digits.push_back(0);
    }
    // 从 long long 构造
    BigInt(long long num) {
        if(num < 0) {
            negative = true;
            num = -num;
        } else {
            negative = false;
        }
        if(num == 0)
            digits.push_back(0);
        while(num) {
            digits.push_back((unsigned int)(num % BASE));
            num /= BASE;
        }
    }
    // 从字符串构造（支持负号）
    BigInt(const string &s) {
        if(s.empty())
            throw runtime_error("Empty string");
        negative = false;
        int start = 0;
        if(s[0] == '-') { negative = true; start = 1; }
        *this = BigInt(0);
        for (int i = start; i < s.size(); i++) {
            if(!isdigit(s[i]))
                throw runtime_error("Invalid input string");
            *this = (*this) * BigInt(10) + BigInt(s[i] - '0');
        }
        trim();
    }

    // 四则运算：加法
    BigInt operator+(const BigInt &other) const {
        BigInt res;
        if(negative == other.negative) {
            res = addAbs(other);
            res.negative = negative;
        } else {
            if(compareAbs(*this, other) >= 0) {
                res = subAbs(other);
                res.negative = negative;
            } else {
                res = other.subAbs(*this);
                res.negative = other.negative;
            }
        }
        res.trim();
        return res;
    }

    // 减法
    BigInt operator-(const BigInt &other) const {
        BigInt temp = other;
        temp.negative = !temp.negative;
        return (*this) + temp;
    }

    // 乘法
    BigInt operator*(const BigInt &other) const {
        BigInt res;
        res.digits.assign(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); i++) {
            unsigned long long carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; j++) {
                unsigned long long cur = res.digits[i+j] +
                    (unsigned long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                res.digits[i+j] = (unsigned int)(cur % BASE);
                carry = cur / BASE;
            }
        }
        res.negative = (negative ^ other.negative);
        res.trim();
        return res;
    }

    // 除法
    BigInt operator/(const BigInt &other) const {
        return divMod(other).first;
    }
    // 取余
    BigInt operator%(const BigInt &other) const {
        return divMod(other).second;
    }

    // 位运算（仅支持非负数，否则抛出异常）
    BigInt operator&(const BigInt &other) const {
        if(negative || other.negative)
            throw runtime_error("位运算只支持非负数");
        BigInt res;
        size_t n = max(digits.size(), other.digits.size());
        res.digits.resize(n, 0);
        for (size_t i = 0; i < n; i++) {
            unsigned int a = i < digits.size() ? digits[i] : 0;
            unsigned int b = i < other.digits.size() ? other.digits[i] : 0;
            res.digits[i] = a & b;
        }
        res.trim();
        return res;
    }
    BigInt operator|(const BigInt &other) const {
        if(negative || other.negative)
            throw runtime_error("位运算只支持非负数");
        BigInt res;
        size_t n = max(digits.size(), other.digits.size());
        res.digits.resize(n, 0);
        for (size_t i = 0; i < n; i++) {
            unsigned int a = i < digits.size() ? digits[i] : 0;
            unsigned int b = i < other.digits.size() ? other.digits[i] : 0;
            res.digits[i] = a | b;
        }
        res.trim();
        return res;
    }
    BigInt operator^(const BigInt &other) const {
        if(negative || other.negative)
            throw runtime_error("位运算只支持非负数");
        BigInt res;
        size_t n = max(digits.size(), other.digits.size());
        res.digits.resize(n, 0);
        for (size_t i = 0; i < n; i++) {
            unsigned int a = i < digits.size() ? digits[i] : 0;
            unsigned int b = i < other.digits.size() ? other.digits[i] : 0;
            res.digits[i] = a ^ b;
        }
        res.trim();
        return res;
    }

    // 左移：按位移动（注意：这里按二进制位移动，移动 k 位，相当于乘以 2^k）
    BigInt operator<<(int k) const {
        if(k < 0) return (*this) >> (-k);
        BigInt res = *this;
        int blockShift = k / 32;
        int bitShift = k % 32;
        // 在低位（digits[0]）前面插入 blockShift 个 0（由于内部是小端存储）
        res.digits.insert(res.digits.begin(), blockShift, 0);
        if(bitShift) {
            unsigned long long carry = 0;
            for (size_t i = 0; i < res.digits.size(); i++) {
                unsigned long long cur = ((unsigned long long)res.digits[i] << bitShift) | carry;
                res.digits[i] = (unsigned int)(cur % BASE);
                carry = cur / BASE;
            }
            if(carry)
                res.digits.push_back((unsigned int)carry);
        }
        res.trim();
        return res;
    }

    // 右移：按位移动（相当于除以 2^k）
    BigInt operator>>(int k) const {
        if(k < 0) return (*this) << (-k);
        BigInt res = *this;
        int blockShift = k / 32;
        int bitShift = k % 32;
        if(blockShift >= (int)res.digits.size())
            return BigInt(0);
        // 删除低位 blockShift 个数字
        res.digits.erase(res.digits.begin(), res.digits.begin() + blockShift);
        if(bitShift) {
            unsigned long long carry = 0;
            for (int i = res.digits.size() - 1; i >= 0; i--) {
                unsigned long long cur = ((unsigned long long)carry << 32) | res.digits[i];
                res.digits[i] = (unsigned int)(cur >> bitShift);
                carry = cur & ((1ULL << bitShift) - 1);
            }
        }
        res.trim();
        return res;
    }

    // 比较运算符
    bool operator<(const BigInt &other) const {
        if(negative != other.negative)
            return negative;
        int cmp = compareAbs(*this, other);
        return negative ? (cmp > 0) : (cmp < 0);
    }
    bool operator>(const BigInt &other) const { return other < *this; }
    bool operator<=(const BigInt &other) const { return !(other < *this); }
    bool operator>=(const BigInt &other) const { return !(*this < other); }
    bool operator==(const BigInt &other) const { return negative == other.negative && digits == other.digits; }
    bool operator!=(const BigInt &other) const { return !(*this == other); }

    // 将高精度数转换为十进制字符串（利用不断除以 10 的方法）
    std::string toString() const {
        if(*this == BigInt(0))
            return "0";
        BigInt temp = *this;
        temp.negative = false;
        std::string s;
        while(temp != BigInt(0)) {
            auto dm = temp.divMod(BigInt(10));
            int digit = dm.second.digits[0];
            s.push_back('0' + digit);
            temp = dm.first;
        }
        if(negative)
            s.push_back('-');
        reverse(s.begin(), s.end());
        return s;
    }

    // 重载输出流
    friend ostream& operator<<(ostream &os, const BigInt &num) {
        os << num.toString();
        return os;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    BigInt a(s), b(t);
    BigInt c = a + b;
    cout << c.toString() << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
