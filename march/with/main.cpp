#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#define N 10000000

namespace with_attributes {
constexpr double pow(double x, long long n) noexcept {
    if (n > 0) [[likely]]
        return x * pow(x, n - 1);
    else [[unlikely]]
        return 1;
}
constexpr long long fact(long long n) noexcept {
    if (n > 1) [[likely]]
        return n * fact(n - 1);
    else [[unlikely]]
        return 1;
}
constexpr double cos(double x) noexcept {
    constexpr long long precision{16LL};
    double y{};
    for (auto n{0LL}; n < precision; n += 2LL) [[likely]]
        y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
    return y;
}
}  // namespace with_attributes

volatile double sink = 0; // ensures a side effect
 
int main()
{
    std::vector<double> numbers;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    for (int i = 0; i < N; ++i) {
        numbers.push_back(dist(gen));
    }
 
    auto benchmark = [&numbers](auto f, auto remark) {
        const auto start = std::chrono::high_resolution_clock::now();
        for (double x : numbers) {
            sink = f(x);
        }
        const std::chrono::duration<double> diff =
            std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
                  << " sec " << remark << std::endl; 
    };
 
    benchmark(with_attributes::cos, "(with attributes)");
}

