#include "all.h"

void day1(cstr in)
{
    auto s = split(in, "\n\n"_s);
    dyn<int> e;
    for(umm i = 0; i < size(s); i++)
    {
        auto x = split(s[i], "\n"_s);
        int c = 0;
        each(x, [&](auto it){ if(size(it)){ c += toint<int>(it); } });
        e.add(c);
    }
    qsort(e, [](auto a, auto b){ return b < a; });
    print("Top: %\n", e[0]);
    print("Sum of top three: %\n", sum(slice(e, 0, 3)));
}

void day2(cstr in)
{
    auto s = split(in, "\n"_s);
    int p = 0;
    int p1 = 0;
    for(umm i = 0; i < size(s); i++)
    {
        if(size(s[i]))
        {
            int a = s[i][0] - 'A';
            int b = s[i][2] - 'X';
            int r = wrap(b - a, -1, 1) + 1;
            p += b + 1 + r * 3;
            int c = wrap(b - 1 + a, 0, 2);
            p1 += c + 1 + b * 3;
        }
    }
    print("Total score: %\n", p);
    print("Total score2: %\n", p1);
}

int main()
{
    try
    {
        dstr in = filestr("day2.txt"_s);
        day2(in);
    }
    catch(const error& e)
    {
        print("Unhandled error: %\n", e.what());
    }
    return 0;
}
