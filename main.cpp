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
    
}

int main()
{
    try
    {
        dstr in = filestr("day1.txt"_s);
        day1(in);
    }
    catch(const error& e)
    {
        print("Unhandled error: %\n", e.what());
    }
    
    return 0;
}
