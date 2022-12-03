#include "all.h"

void day1(cstr in)
{
    dyn<int> e;
    split(in, "\n\n"_s, [&](auto it)
          {
              int c = 0;
              split(it, "\n"_s, [&](auto x)
                    {
                        if(size(x)) c += toint<int>(x);
                    });
              e.add(c);
          });
    qsort(e, [](auto a, auto b){ return b < a; });
    print("Top: %\n", e[0]);
    print("Sum of top three: %\n", sum(slice(e, 0, 3)));
}

void day2(cstr in)
{
    int p = 0;
    int p1 = 0;
    split(in, "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  int a = it[0] - 'A';
                  int b = it[2] - 'X';
                  int r = wrap(b - a, -1, 1) + 1;
                  p += b + 1 + r * 3;
                  int c = wrap(b - 1 + a, 0, 2);
                  p1 += c + 1 + b * 3;
              }
          });
    print("Total score: %\n", p);
    print("Total score2: %\n", p1);
}

void day3(cstr in)
{
    auto s = split(in, "\n"_s);
    int p = 0;
    for(umm i = 0; i < size(s); i++)
    {
        auto it = s[i];
        if(size(it))
        {
            auto a = slice(it, 0, size(it) / 2);
            auto b = slice(it, size(it) / 2);
            for(umm j = 0; j < size(a); j++)
            {
                if(find(b, a[j]) != -1)
                {
                    int prio = 0;
                    if(a[j] >= 'a' && a[j] <= 'z') prio = a[j] - 'a' + 1;
                    if(a[j] >= 'A' && a[j] <= 'Z') prio = a[j] - 'A' + 1 + 26;
                    p += prio;
                    break;
                }
            }
        }
    }
    print("Sum: %\n", p);
    
    p = 0;
    for(umm i = 0; i < size(s); i += 3)
    {
        if(i + 2 < size(s))
        {
            auto a = s[i];
            auto b = s[i + 1];
            auto c = s[i + 2];
            for(umm j = 0; j < size(a); j++)
            {
                if(find(b, a[j]) != -1 && find(c, a[j]) != -1)
                {
                    int prio = 0;
                    if(a[j] >= 'a' && a[j] <= 'z') prio = a[j] - 'a' + 1;
                    if(a[j] >= 'A' && a[j] <= 'Z') prio = a[j] - 'A' + 1 + 26;
                    p += prio;
                    break;
                }
            }
        }
    }
    print("Sum: %\n", p);
}

int main()
{
    try
    {
        dstr in = filestr("day3.txt"_s);
        day3(in);
    }
    catch(const error& e)
    {
        print("Unhandled error: %\n", e.what());
    }
    return 0;
}
