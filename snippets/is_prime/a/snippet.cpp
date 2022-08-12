bool is_prime(int n)
{
    for (int i = 2; i * i < n; ++i) {
        if (n % i == 0) {
            [[unlikely]]
            return false;
        }
    }
    return true;
}
