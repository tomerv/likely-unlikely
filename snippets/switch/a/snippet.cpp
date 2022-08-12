int foo0();
int foo1();
int foo2();
int foo3();
int foo4();
int foo5();
int foo6();
int foo7();
int foo8();
int foo9();
int bar(int);

int foo(int x)
{
    switch (x)
    {
        case 0:
            return foo0();
        case 1:
            return foo1();
        case 2:
            return foo2();
        case 3:
            return foo3();
        case 4:
            return foo4();
        [[unlikely]] case 5:
            return foo5();
        case 6:
            return foo6();
        [[likely]] case 7:
            return foo7();
        case 8:
            return foo8();
        case 9:
            return foo9();
        default:
            return bar(x);

    }
}

