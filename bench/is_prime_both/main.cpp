#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#define N 10000000
#define M 10000000

// bool is_prime(int n)
// {
//     for (int i = 2; i * i < n; ++i) {
//         if (n % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }

bool is_prime_likely(int n)
{
    for (int i = 2; i * i < n; ++i) {
        if (n % i == 0) {
            [[likely]]
            return false;
        }
    }
    return true;
}

bool is_prime_unlikely(int n)
{
    for (int i = 2; i * i < n; ++i) {
        if (n % i == 0) {
            [[unlikely]]
            return false;
        }
    }
    return true;
}


volatile bool sink = 0; // ensures a side effect
 
int main()
{
    std::vector<int> numbers;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(2, M);
    for (int i = 0; i < N; ++i) {
        numbers.push_back(dist(gen));
    }
 
    auto benchmark = [&numbers](auto f, auto remark) {
        const auto start = std::chrono::high_resolution_clock::now();
        for (int n : numbers) {
            sink = f(n);
        }
        const std::chrono::duration<double> diff =
            std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
                  << " sec " << remark << std::endl; 
    };
 
    // benchmark(is_prime, "(no attributes)");
    benchmark(is_prime_likely, "([[likely]])");
    benchmark(is_prime_unlikely, "([[unlikely]])");
}

