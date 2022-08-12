int log2_likely(int n)
{
    int res = -1;
    while (n > 0) { [[likely]]
        res++;
        n /= 2;
    }
    return res;
}

