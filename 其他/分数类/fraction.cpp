#include <iostream>
#include <numeric>
#include <concepts>
#include <compare>

class Fraction {
private:
    using i64 = long long;
    i64 num, den;

    void normalize() {
        i64 g = std::gcd(num, den);
        num /= g; den /= g;
        if (den < 0) { num = -num; den = -den; }
    }

public:
    Fraction(i64 n = 0, i64 d = 1) : num(n), den(d) {
        if (den == 0) throw std::invalid_argument("Zero denominator");
        normalize();
    }

    explicit operator double() const { return static_cast<double>(num) / den; }

    // 算术运算符
    Fraction operator+() const { return *this; }
    Fraction operator-() const { return {-num, den}; }

    Fraction &operator+=(const Fraction &rhs) {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        normalize();
        return *this;
    }

    Fraction &operator-=(const Fraction &rhs) { return *this += -rhs; }
    Fraction &operator*=(const Fraction &rhs) {
        num *= rhs.num;
        den *= rhs.den;
        normalize();
        return *this;
    }

    Fraction &operator/=(const Fraction &rhs) {
        return *this *= {rhs.den, rhs.num};
    }

    // 友元运算符模板
    template<std::integral T>
    friend Fraction operator+(Fraction lhs, T rhs) { return lhs += rhs; }

    template<std::integral T>
    friend Fraction operator+(T lhs, Fraction rhs) { return rhs += lhs; }

    friend Fraction operator+(Fraction lhs, const Fraction &rhs) { return lhs += rhs; }

    template<std::floating_point T>
    friend auto operator+(Fraction f, T d) { return static_cast<double>(f) + d; }

    template<std::floating_point T>
    friend auto operator+(T d, Fraction f) { return d + static_cast<double>(f); }

    // 其他运算符通过第一个运算符定义
    friend Fraction operator-(Fraction lhs, const Fraction &rhs) { return lhs -= rhs; }
    friend Fraction operator*(Fraction lhs, const Fraction &rhs) { return lhs *= rhs; }
    friend Fraction operator/(Fraction lhs, const Fraction &rhs) { return lhs /= rhs; }

    // 三路比较运算符（C++20）
    auto operator<=>(const Fraction &rhs) const {
        return num * rhs.den <=> rhs.num * den;
    }

    bool operator==(const Fraction &rhs) const = default;

    template<typename T> requires std::integral<T> || std::floating_point<T>
    auto operator<=>(T val) const {
        if constexpr (std::integral<T>)
            return *this <=> Fraction(val);
        else
            return static_cast<double>(*this) <=> val;
    }

    // 流运算符
    friend std::ostream &operator<<(std::ostream &os, const Fraction &f) {
        return f.den == 1 ? os << f.num : os << f.num << '/' << f.den;
    }

    friend std::istream &operator>>(std::istream &is, Fraction &f) {
        i64 n, d = 1;
        char c;
        is >> n;
        if (is.peek() == '/') is >> c >> d;
        f = Fraction(n, d);
        return is;
    }
};

int main() {
    // 测试代码
    Fraction a(3, 4), b(2, 3);
    std::cout << "a + b = " << a + b << "\n";      // 17/12
    std::cout << "a - 1 = " << a - 1 << "\n";      // -1/4
    std::cout << "2 * b = " << 2 * b << "\n";      // 4/3

    auto c = a + 5LL; // 使用long long
    std::cout << "c = " << c << "\n";              // 23/4

    double d = b + 0.5;
    std::cout << "d = " << d << "\n";              // 0.5 + 0.666667 ≈ 1.16667

    std::cout << std::boolalpha
        << "a > 0.7: " << (a > 0.7) << "\n"  // true
        << "b < 1: " << (b < 1) << "\n";     // true

    try {
        Fraction f(1, 0);
    }
    catch (const std::exception &e) {
        std::cout << "Exception: " << e.what();    // Zero denominator
    }
}