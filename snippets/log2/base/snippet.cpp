int log2(int n)
{
    int res = -1;
    while (n > 0) {
        res++;
        n /= 2;
    }
    return res;
}

