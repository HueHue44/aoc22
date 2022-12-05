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

void day4(cstr in)
{
    int p = 0;
    int p1 = 0;
    split(in, "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  auto x = split(it, ","_s);
                  auto r1 = split(x[0], "-"_s);
                  auto r2 = split(x[1], "-"_s);
                  int a = toint<int>(r1[0]);
                  int b = toint<int>(r1[1]);
                  int c = toint<int>(r2[0]);
                  int d = toint<int>(r2[1]);
                  if(a >= c && b <= d) p++;
                  else if(c >= a && d <= b) p++;
                  if(a >= c && a <= d || b >= c && b <= d) p1++;
                  else if(c >= a && c <= b || d >= a && d <= b) p1++;
              }
          });
    print("Full containment in % assignments\n", p);
    print("Overlap in % assignments\n", p1);
}

void day5(cstr in)
{
    auto a = split(in, "\n\n"_s);
    dyn<dyn<char>> s;
    split(a[0], "\n"_s, [&](auto it)
          {
              if(size(it) && it[1] != '1')
              {
                  s.resize((size(it) + 1) / 4);
                  for(umm i = 0; i < size(s); i++) if(it[(i * 4) + 1] != ' ') s[i].insert(0, it[(i * 4) + 1]);
              }
          });
    auto s1 = s;
    split(a[1], "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  auto c = split(it, " "_s);
                  int n = toint<int>(c[1]);
                  int i0 = toint<int>(c[3]) - 1;
                  int i1 = toint<int>(c[5]) - 1;
                  auto& a = s[i0];
                  auto& b = s[i1];
                  for(umm i = 0; i < n; i++)
                  {
                      b.add(a[size(a) - 1]);
                      a.remove(size(a) - 1);
                  }
                  auto& x = s1[i0];
                  auto& y = s1[i1];
                  y.place(slice(x, size(x) - n, n));
                  x.remove(size(x) - n, n);
              }
          });
    each(s, [&](auto x){ print("%", x[size(x) - 1]); });
    print("\n");
    each(s1, [&](auto x){ print("%", x[size(x) - 1]); });
    print("\n");
}

int main()
{
    try
    {
        dstr in = filestr("day5.txt"_s);
        day5(in);
    }
    catch(const error& e)
    {
        print("Unhandled error: %\n", e.what());
    }
    return 0;
}
