int log2_unlikely(int n)
{
    int res = -1;
    while (n > 0) { [[unlikely]]
        res++;
        n /= 2;
    }
    return res;
}

