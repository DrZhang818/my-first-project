#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


///////////////////////
// 高精度整数 BigInt
///////////////////////
class BigInt {
private:
    // 内部采用 2^32 为基，以小端方式存储
    static const unsigned long long BASE = 1ULL << 32;
    vector<unsigned int> digits;  // digits[0] 为最低位
    bool negative;  // false 表示非负，true 表示负数

    // 去除多余的高位 0
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
        for (int i = a.digits.size()-1; i >= 0; i--) {
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
    
    // 绝对值相减（假定 *this >= other 且均为正）
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
    
    // 长除法：返回 <商,余数>
    pair<BigInt, BigInt> divMod(const BigInt &other) const {
        if(other == BigInt(0))
            throw runtime_error("Division by zero");
        BigInt divisor = other; divisor.negative = false;
        BigInt dividend = *this; dividend.negative = false;
        BigInt quotient;
        quotient.digits.resize(dividend.digits.size(), 0);
        BigInt remainder(0);
        for (int i = dividend.digits.size()-1; i >= 0; i--) {
            remainder = remainder << 32;
            remainder.digits[0] = dividend.digits[i];
            remainder.trim();
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
    
    // 从字符串构造（只支持整数形式，可用于 BigDecimal 内部构造）
    BigInt(const string &s) {
        negative = false;
        int start = 0;
        if(s[0] == '-') { negative = true; start = 1; }
        *this = BigInt(0);
        for (int i = start; i < s.size(); i++) {
            if(!isdigit(s[i]))
                throw runtime_error("Invalid input string for BigInt");
            *this = (*this) * BigInt(10) + BigInt(s[i]-'0');
        }
        trim();
    }
    
    // 四则运算
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
    
    BigInt operator-(const BigInt &other) const {
        BigInt temp = other;
        temp.negative = !temp.negative;
        return (*this) + temp;
    }
    
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
    
    BigInt operator/(const BigInt &other) const {
        return divMod(other).first;
    }
    
    BigInt operator-() const {
        BigInt res = *this;
        if (res != BigInt(0))  // 避免对0取反引入负号
            res.negative = !res.negative;
        return res;
    }

    BigInt operator%(const BigInt &other) const {
        return divMod(other).second;
    }
    
    // 左移（按二进制位移动，相当于乘以 2^k）
    BigInt operator<<(int k) const {
        if(k < 0) return (*this) >> (-k);
        BigInt res = *this;
        int blockShift = k / 32;
        int bitShift = k % 32;
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
    
    // 右移（按二进制位移动，相当于除以 2^k）
    BigInt operator>>(int k) const {
        if(k < 0) return (*this) << (-k);
        BigInt res = *this;
        int blockShift = k / 32;
        int bitShift = k % 32;
        if(blockShift >= (int)res.digits.size())
            return BigInt(0);
        res.digits.erase(res.digits.begin(), res.digits.begin() + blockShift);
        if(bitShift) {
            unsigned long long carry = 0;
            for (int i = res.digits.size()-1; i >= 0; i--) {
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
    
    // 转为十进制字符串
    string toString() const {
        if(*this == BigInt(0))
            return "0";
        BigInt temp = *this;
        temp.negative = false;
        string s;
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
    
    friend ostream& operator<<(ostream &os, const BigInt &num) {
        os << num.toString();
        return os;
    }
};

///////////////////////
// 高精度小数 BigDecimal
///////////////////////
class BigDecimal {
private:
    // 内部表示：integer * 10^(-scale)
    BigInt integer;
    int scale;  // 小数部分位数

public:
    // 默认构造，表示 0
    BigDecimal(): integer(0), scale(0) {}
    
    // 从字符串构造，支持形如 "123.456", "-0.789" 等格式
    BigDecimal(const string &s) {
        bool neg = false;
        int start = 0;
        if(s[0] == '-') { neg = true; start = 1; }
        else if(s[0] == '+') { start = 1; }
        size_t pointPos = s.find('.', start);
        string intPart, fracPart;
        if(pointPos == string::npos) {
            intPart = s.substr(start);
            fracPart = "";
            scale = 0;
        } else {
            intPart = s.substr(start, pointPos - start);
            fracPart = s.substr(pointPos + 1);
            scale = fracPart.size();
        }
        string combined = intPart + fracPart;
        if(combined == "")
            combined = "0";
        integer = BigInt(combined);
        if(neg && integer != BigInt(0))
            integer = -integer;
    }
    
    // 从 BigInt 与 scale 构造
    BigDecimal(const BigInt &i, int s): integer(i), scale(s) {}
    
    // 辅助函数：计算 10 的 exp 次幂（BigInt 类型）
    static BigInt power10(int exp) {
        BigInt result(1);
        for(int i = 0; i < exp; i++)
            result = result * BigInt(10);
        return result;
    }
    
    // 加法：将两个小数对齐后直接加减整数部分
    BigDecimal operator+(const BigDecimal &other) const {
        int newScale = max(scale, other.scale);
        BigInt factor1 = power10(newScale - scale);
        BigInt factor2 = power10(newScale - other.scale);
        BigInt newInt = integer * factor1 + other.integer * factor2;
        return BigDecimal(newInt, newScale);
    }
    
    // 减法
    BigDecimal operator-(const BigDecimal &other) const {
        int newScale = max(scale, other.scale);
        BigInt factor1 = power10(newScale - scale);
        BigInt factor2 = power10(newScale - other.scale);
        BigInt newInt = integer * factor1 - other.integer * factor2;
        return BigDecimal(newInt, newScale);
    }
    
    // 四舍五入/截断：将小数调整为 newScale 位小数
    // 参数 roundHalfUp 为 true 时采用四舍五入，为 false 时直接截断
    BigDecimal round(int newScale, bool roundHalfUp) const {
        if(newScale >= scale) {
            // 扩大精度（相当于在末尾补 0）
            BigInt factor = power10(newScale - scale);
            return BigDecimal(integer * factor, newScale);
        } else {
            int diff = scale - newScale;
            BigInt factor = power10(diff);
            BigInt quotient = integer / factor;
            BigInt remainder = integer % factor;
            // 对于负数取绝对值
            BigInt absRemainder = (remainder < BigInt(0)) ? -remainder : remainder;
            if(roundHalfUp) {
                BigInt two(2);
                if(absRemainder * two >= factor) {
                    if(integer < BigInt(0))
                        quotient = quotient - BigInt(1);
                    else
                        quotient = quotient + BigInt(1);
                }
            }
            return BigDecimal(quotient, newScale);
        }
    }
    
    // 将 BigDecimal 转为字符串输出
    string toString() const {
        string s = integer.toString();
        bool neg = false;
        if(s[0] == '-') {
            neg = true;
            s = s.substr(1);
        }
        if(scale == 0)
            return (neg ? "-" : "") + s;
        // 若整数部分位数不足，则在前面补 0
        if(s.size() <= (size_t)scale)
            s = string(scale - s.size() + 1, '0') + s;
        // 插入小数点
        s.insert(s.size() - scale, ".");
        return (neg ? "-" : "") + s;
    }
    
    friend ostream& operator<<(ostream &os, const BigDecimal &bd) {
        os << bd.toString();
        return os;
    }
};


void solve() { 
    int n;
    string s;
    cin >> n >> s;
    BigDecimal a(s);
    for(int i = 0; i < n; i++) {
        a = a + a;
    }
    a = a.round(0, true);
    string ans = a.toString();
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
