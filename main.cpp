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

void day6(cstr in)
{
    umm p = (umm)-1;
    for(umm i = 0; i < size(in) - 4; i++)
    {
        auto s = slice(in, i, 4);
        p = i + size(s);
        for(umm j = 0; j < size(s); j++)
        {
            for(umm k = j; k < size(s); k++)
            {
                if(j != k && s[j] == s[k]) p = (umm)-1;
            }
        }
        if(p != -1) break;
    }
    print("Start of packet %\n", p);
    
    p = (umm)-1;
    for(umm i = 0; i < size(in) - 14; i++)
    {
        auto s = slice(in, i, 14);
        p = i + size(s);
        for(umm j = 0; j < size(s); j++)
        {
            for(umm k = j; k < size(s); k++)
            {
                if(j != k && s[j] == s[k]) p = (umm)-1;
            }
        }
        if(p != -1) break;
    }
    print("Start of message %\n", p);
}

void day7(cstr in)
{
    dyn<dstr> a;
    dyn<int> s;
    dstr d;
    split(in, "\n"_s, [&](auto it)
          {
              if(!size(it)) return;
              auto x = split(it, " "_s);
              if(x[0] == "$"_s)
              {
                  if(x[1] == "cd"_s)
                  {
                      if(x[2] == ".."_s)
                      {
                          d.remove(size(d) - 1);
                          umm l = find_last(d, '/');
                          d.remove(l + 1, size(d) - l - 1);
                      }
                      else
                      {
                          if(x[2] == "/"_s)
                          {
                              d = "/"_s;
                          }
                          else
                          {
                              d.place(x[2]);
                              d.add('/');
                          }
                          if(find(a, d) == -1)
                          {
                              a.add(d);
                              s.add(0);
                          }
                      }
                  }
              }
              else if(x[0] == "dir"_s)
              {
              }
              else
              {
                  int b = toint<int>(x[0]);
                  for(umm i = 0; i < size(a); i++)
                  {
                      if(match(d, a[i]) == 0)
                      {
                          s[i] += b;
                      }
                  }
              }
          });
    int p = 0;
    int p1 = 70000000;
    for(umm i = 0; i < size(a); i++)
    {
        if(s[i] <= 100000) p += s[i];
        if(70000000 - s[0] + s[i] >= 30000000) p1 = min(p1, s[i]);
    }
    print("Total size: %\n", p);
    print("Smallest total: %\n", p1);
}

void day8(cstr in)
{
    sta<sta<int, 99>, 99> m;
    for(umm y = 0; y < 99; y++)
    {
        for(umm x = 0; x < 99; x++)
        {
            m[y][x] = in[y * 100 + x] - '0';
        }
    }
    int p = 0;
    for(umm y = 0; y < 99; y++)
    {
        for(umm x = 0; x < 99; x++)
        {
            umm i = 0;
            while(i < x && m[y][i] < m[y][x]) i++;
            if(i == x)
            {
                p++;
                continue;
            }
            i = 98;
            while(i > x && m[y][i] < m[y][x]) i--;
            if(i == x)
            {
                p++;
                continue;
            }
            i = 0;
            while(i < y && m[i][x] < m[y][x]) i++;
            if(i == y)
            {
                p++;
                continue;
            }
            i = 98;
            while(i > y && m[i][x] < m[y][x]) i--;
            if(i == y)
            {
                p++;
                continue;
            }
        }
    }
    print("Total visible trees: %\n", p);
    umm p1 = 0;
    for(umm y = 0; y < 99; y++)
    {
        for(umm x = 0; x < 99; x++)
        {
            umm a = x + (x != 98);
            while(a < 98 && m[y][a] < m[y][x]) a++;
            umm b = x - (x != 0);
            while(b > 0 && m[y][b] < m[y][x]) b--;
            umm c = y + (y != 98);
            while(c < 98 && m[c][x] < m[y][x]) c++;
            umm d = y - (y != 0);
            while(d > 0 && m[d][x] < m[y][x]) d--;
            p1 = max(p1, (a - x) * (x - b) * (c - y) * (y - d));
        }
    }
    print("Highest score: %\n", p1);
}

void day9(cstr in)
{
    {
        dyn<sta<int, 2>> v;
        sta h = {{ 0, 0 }};
        sta t = {{ 0, 0 }};
        v.add(t);
        split(in, "\n"_s, [&](auto it)
              {
                  if(!size(it)) return;
                  auto x = split(it, " "_s);
                  sta m = {{0, 0}};
                  if(x[0] == "L"_s) m[0] -= 1;
                  if(x[0] == "R"_s) m[0] += 1;
                  if(x[0] == "D"_s) m[1] -= 1;
                  if(x[0] == "U"_s) m[1] += 1;
                  int n = toint<int>(x[1]);
                  for(umm i = 0; i < n; i++)
                  {
                      h += m;
                      auto d = h - t;
                      if(d[0] < -1) t = h + sta{{ 1, 0 }};
                      if(d[0] > 1)  t = h - sta{{ 1, 0 }};
                      if(d[1] < -1) t = h + sta{{ 0, 1 }};
                      if(d[1] > 1)  t = h - sta{{ 0, 1 }};
                      if(find(v, t) == -1) v.add(t);
                  }
              });
        print("Unique locations: %\n", size(v));
    }
    {
        dyn<sta<int, 2>> v;
        sta<sta<int, 2>, 10> r{};
        v.add(r[size(r) - 1]);
        split(in, "\n"_s, [&](auto it)
              {
                  if(!size(it)) return;
                  auto x = split(it, " "_s);
                  sta m = {{0, 0}};
                  if(x[0] == "L"_s) m[0] -= 1;
                  if(x[0] == "R"_s) m[0] += 1;
                  if(x[0] == "D"_s) m[1] -= 1;
                  if(x[0] == "U"_s) m[1] += 1;
                  int n = toint<int>(x[1]);
                  for(umm i = 0; i < n; i++)
                  {
                      r[0] += m;
                      for(umm j = 1; j < size(r); j++)
                      {
                          auto d = r[j - 1] - r[j];
                          if(abs(d[0]) == 2 && abs(d[1]) == 2)
                          {
                              d[0] /= 2;
                              d[1] /= 2;
                              r[j] += d;
                          }
                          else
                          {
                              if(d[0] < -1) r[j] = r[j - 1] + sta{{ 1, 0 }};
                              if(d[0] > 1)  r[j] = r[j - 1] - sta{{ 1, 0 }};
                              if(d[1] < -1) r[j] = r[j - 1] + sta{{ 0, 1 }};
                              if(d[1] > 1)  r[j] = r[j - 1] - sta{{ 0, 1 }};
                          }
                      }
                      if(find(v, r[size(r) - 1]) == -1) v.add(r[size(r) - 1]);
                  }
              });
        print("Unique locations: %\n", size(v));
    }
}

void day10(cstr in)
{
    int p = 0;
    int c = 0;
    int x = 1;
    int t = 20;
    dstr o;
    split(in, "\n"_s, [&](auto it)
          {
              if(!size(it)) return;
              auto s = split(it, " "_s);
              int a = 0;
              if(s[0] == "addx"_s)
              {
                  a = toint<int>(s[1]);
                  c += 2;
                  if((int)(size(o) % 40) >= x - 1 && (int)(size(o) % 40) <= x + 1)
                  {
                      o.add('#');
                  }
                  else
                  {
                      o.add('.');
                  }
              }
              else
              {
                  c++;
              }
              if(c >= t)
              {
                  p += t * x;
                  t += 40;
              }
              
              if((int)(size(o) % 40) >= x - 1 && (int)(size(o) % 40) <= x + 1)
              {
                  o.add('#');
              }
              else
              {
                  o.add('.');
              }
              
              x += a;
          });
    for(umm i = 40; i < size(o); i += 40) o.insert(i++, '\n');
    print("Sum of signal strength: %\n", p);
    print("%\n", o);
}

void day11(cstr in)
{
    auto t = split(in, "\n\n"_s);
    dyn<dyn<u64>> m;
    dyn<dyn<u64>> m1;
    u64 mod = 1;
    for(umm i = 0; i < size(t); i++)
    {
        auto x = split(t[i], "\n"_s);
        auto y = split(x[1], ": "_s);
        auto n = split(y[1], ", "_s);
        dyn<u64> a;
        each(n, [&](const auto& it){ a.add(toint<u64>(it)); });
        m.add(a);
        m1.add(a);
        mod *= toint<u64>(split(x[3], "by "_s)[1]);
    }
    dyn<u64> p(size(m));
    for(umm r = 0; r < 20; r++)
    {
        for(umm i = 0; i < size(t); i++)
        {
            auto& l = m[i];
            auto s = split(t[i], "\n"_s);
            auto o = split(s[2], " "_s);
            auto d1 = split(s[3], "by "_s);
            auto x1 = split(s[4], "monkey "_s);
            auto y1 = split(s[5], "monkey "_s);
            auto d = toint<u64>(d1[1]);
            auto x = toint<u64>(x1[1]);
            auto y = toint<u64>(y1[1]);
            while(size(l))
            {
                u64 a = l[0];
                l.remove(0);
                u64 b = 0;
                if(o[7] == "old"_s) b = a;
                else b = toint<u64>(o[7]);
                if(o[6] == "*"_s) a = a * b;
                else a = a + b;
                a /= 3;
                if((a % d) == 0) m[x].add(a);
                else m[y].add(a);
                p[i]++;
            }
        }
    }
    qsort(p, [](auto a, auto b){ return b < a; });
    print("Level of monkey business: %\n", p[0] * p[1]);
    dyn<u64> p1(size(m1));
    for(umm r = 0; r < 10000; r++)
    {
        for(umm i = 0; i < size(t); i++)
        {
            auto& l = m1[i];
            auto s = split(t[i], "\n"_s);
            auto o = split(s[2], " "_s);
            auto d1 = split(s[3], "by "_s);
            auto x1 = split(s[4], "monkey "_s);
            auto y1 = split(s[5], "monkey "_s);
            auto d = toint<u64>(d1[1]);
            auto x = toint<u64>(x1[1]);
            auto y = toint<u64>(y1[1]);
            while(size(l))
            {
                u64 a = l[0];
                l.remove(0);
                u64 b = 0;
                if(o[7] == "old"_s) b = a;
                else b = toint<u64>(o[7]);
                if(o[6] == "*"_s) a = a * b;
                else a = a + b;
                a %= mod;
                if((a % d) == 0) m1[x].add(a);
                else m1[y].add(a);
                p1[i]++;
            }
        }
    }
    qsort(p1, [](auto a, auto b){ return b < a; });
    print("Level of monkey business: %\n", p1[0] * p1[1]);
}

void day12(cstr in)
{
    auto f = [&](umm x, umm y)
    {
        auto g = split(slice(in, 0, size(in) - 1), "\n"_s);
        g[20][0] = 'a';
        umm w = size(g[0]);
        umm h = size(g);
        dyn<sta<umm, 4>> q;
        q.add({{ x, y, 'a', 0 }});
        umm p = (umm)-1;
        while(size(q))
        {
            auto it = q[0];
            q.remove(0);
            if(it[0] < w && it[1] < h && g[it[1]][it[0]] <= it[2] + 1)
            {
                umm d = g[it[1]][it[0]];
                if(d == 'E')
                {
                    p = it[3];
                    break;
                }
                g[it[1]][it[0]]= '~';
                q.add({{ it[0] - 1, it[1], d, it[3] + 1 }});
                q.add({{ it[0] + 1, it[1], d, it[3] + 1 }});
                q.add({{ it[0], it[1] - 1, d, it[3] + 1 }});
                q.add({{ it[0], it[1] + 1, d, it[3] + 1 }});
            }
        }
        return p;
    };
    print("Fewest steps: %\n", f(0, 20));
    umm p = (umm)-1;
    umm x = 0;
    umm y = 0;
    for(umm i = 0; i < size(in); i++)
    {
        if(in[i] == '\n')
        {
            x = 0;
            y++;
        }
        else
        {
            if(in[i] == 'a' || in[i] == 'S') p = min(p, f(x, y));
            x++;
        }
    }
    print("Fewest steps overall: %\n", p);
}

void day13(cstr in)
{
    auto csv = [&](cstr x)
    {
        dyn<cstr> r;
        umm c = 0;
        umm s = 1;
        for(umm i = 1; i < size(x); i++)
        {
            if(x[i] == '[') c++;
            else if(x[i] == ']') c--;
            else if(x[i] == ',' && c == 0)
            {
                r.add(slice(x, s, i - s));
                s = i + 1;
            }
        }
        if(size(x) - s - 1) r.add(slice(x, s, size(x) - s - 1));
        return r;
    };
    
    auto cmp = [&](auto f, cstr a, cstr b) -> int
    {
        if(a[0] == '[' && b[0] == '[')
        {
            auto ac = csv(a);
            auto bc = csv(b);
            for(umm i = 0; i < size(ac) && i < size(bc); i++)
            {
                int r = f(f, ac[i], bc[i]);
                if(r) return r;
            }
            return size(ac) < size(bc) ? -1 : size(bc) < size(ac) ? 1 : 0;
        }
        else
        {
            if(b[0] == '[') return f(f, fmt("[%]", a), b);
            if(a[0] == '[') return f(f, a, fmt("[%]", b));
            return toint<int>(a) < toint<int>(b) ? -1 : toint<int>(b) < toint<int>(a) ? 1 : 0;
        }
    };
    
    dyn<dstr> all;
    umm p = 0;
    auto x = split(in, "\n\n"_s);
    for(umm i = 0; i < size(x); i++)
    {
        auto s = split(x[i], "\n"_s);
        if(cmp(cmp, s[0], s[1]) == -1) p += i + 1;
        all.add(s[0], s[1]);
    }
    print("Sum of indices: %\n", p);
    
    all.add("[[2]]"_s, "[[6]]"_s);
    qsort(all, [&](const auto& a, const auto& b){ return cmp(cmp, a, b) == -1; });
    print("Decoder key: %\n", (find(all, "[[2]]"_s) + 1) * (find(all, "[[6]]"_s) + 1));
}

void day14(cstr in)
{
    dyn<sta<int, 2>> g;
    int y = 0;
    split(in, "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  auto c = split(it, " -> "_s);
                  for(umm i = 1; i < size(c); i++)
                  {
                      sta<int, 2> a = { toint<int>(split(c[i - 1], ","_s)[0]), toint<int>(split(c[i - 1], ","_s)[1]) };
                      sta<int, 2> b = { toint<int>(split(c[i], ","_s)[0]), toint<int>(split(c[i], ","_s)[1]) };
                      y = max(y, a[1]);
                      y = max(y, b[1]);
                      auto d = b - a;
                      d[0] = sign(d[0]);
                      d[1] = sign(d[1]);
                      g.add(a);
                      while(a != b)
                      {
                          a += d;
                          g.add(a);
                      }
                  }
              }
          });
    auto g1 = g;
    umm p = 0;
    sta<int, 2> x = { 500, 0 };
    while(x[1] < y)
    {
        if(find(g, x + sta<int, 2>{ 0, 1 }) == -1)       x += sta<int, 2>{ 0, 1 };
        else if(find(g, x + sta<int, 2>{ -1, 1 }) == -1) x += sta<int, 2>{ -1, 1 };
        else if(find(g, x + sta<int, 2>{ 1, 1 }) == -1)  x += sta<int, 2>{ 1, 1 };
        else
        {
            p++;
            g.add(x);
            x = { 500, 0 };
        }
    }
    print("Units of sand: %\n", p);
    
    g = g1;
    umm p1 = 0;
    x = { 500, 0 };
    while(true)
    {
        if(find(g, x + sta<int, 2>{ 0, 1 }) == -1 && x[1] < y + 1)       x += sta<int, 2>{ 0, 1 };
        else if(find(g, x + sta<int, 2>{ -1, 1 }) == -1 && x[1] < y + 1) x += sta<int, 2>{ -1, 1 };
        else if(find(g, x + sta<int, 2>{ 1, 1 }) == -1 && x[1] < y + 1)  x += sta<int, 2>{ 1, 1 };
        else
        {
            p1++;
            g.add(x);
            if(x == sta<int, 2>{ 500, 0 }) break;
            x = { 500, 0 };
        }
    }
    print("Units of sand: %\n", p1);
}

void day15(cstr in)
{
    dyn<sta<int, 2>> s;
    dyn<sta<int, 2>> b;
    split(in, "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  auto x = split(it, "x="_s);
                  auto y = split(it, "y="_s);
                  s.add(sta<int, 2>{ toint<int>(split(x[1], ","_s)[0]), toint<int>(split(y[1], ":"_s)[0]) });
                  b.add(sta<int, 2>{ toint<int>(split(x[2], ","_s)[0]), toint<int>(y[2]) });
              }
          });
    {
        int y = 2000000;
        dyn<sta<int, 2>> r;
        for(umm i = 0; i < size(s); i++)
        {
            auto m = abs(s[i][0] - b[i][0]) + abs(s[i][1] - b[i][1]);
            int d = m - abs(y - s[i][1]);
            if(d >= 0)
            {
                int x0 = s[i][0] - d;
                int x1 = s[i][0] + d;
                r.add({{ x0, x1 }});
            }
        }
        for(umm i = 0; i < size(r); i++)
        {
            for(umm j = 0; j < size(r); j++)
            {
                if(i == j) continue;
                auto& a = r[i];
                auto& b = r[j];
                if((a[0] >= b[0] && a[0] <= b[1]) || (a[1] >= b[0] && a[1] <= b[1]) ||
                   (b[0] >= a[0] && b[0] <= a[1]) || (b[1] >= a[0] && b[1] <= a[1]))
                {
                    a[0] = min(a[0], b[0]);
                    a[1] = max(a[1], b[1]);
                    r.remove(j);
                    i = 0;
                    break;
                }
            }
        }
        int p = 0;
        for(umm i = 0; i < size(r); i++) p += r[i][1] - r[i][0];
        print("Positions that do not contain a beacon: %\n", p);
    }
    
    for(int y = 0; y < 4000000; y++)
    {
        dyn<sta<int, 2>> r;
        for(umm i = 0; i < size(s); i++)
        {
            auto m = abs(s[i][0] - b[i][0]) + abs(s[i][1] - b[i][1]);
            int d = m - abs(y - s[i][1]);
            if(d >= 0)
            {
                int x0 = s[i][0] - d;
                int x1 = s[i][0] + d;
                r.add({{ x0, x1 }});
            }
        }
        for(umm i = 0; i < size(r); i++)
        {
            for(umm j = 0; j < size(r); j++)
            {
                if(i == j) continue;
                auto& a = r[i];
                auto& b = r[j];
                if((a[0] >= b[0] && a[0] <= b[1]) || (a[1] >= b[0] && a[1] <= b[1]) ||
                   (b[0] >= a[0] && b[0] <= a[1]) || (b[1] >= a[0] && b[1] <= a[1]))
                {
                    a[0] = min(a[0], b[0]);
                    a[1] = max(a[1], b[1]);
                    r.remove(j);
                    i = 0;
                    break;
                }
            }
        }
        for(umm i = 0; i < size(r); i++)
        {
            if(r[i][1] >= 0 && r[i][1] <= 4000000)
            {
                print("Tuning frequency: %\n", (s64)(r[i][1] + 1) * 4000000 + y);
            }
        }
    }
}

void day16(cstr in)
{
    dyn<dstr> v;
    dyn<int> r;
    dyn<dyn<dstr>> p;
    split(in, "\n"_s, [&](auto it)
          {
              if(size(it))
              {
                  auto x = split(it, " "_s);
                  v.add(x[1]);
                  r.add(toint<int>(split(slice(x[4], 0, size(x[4]) - 1), "="_s)[1]));
                  auto y = split(it, "valves "_s);
                  if(size(y) < 2) y = split(it, "valve "_s);
                  p.add(split(y[1], ", "_s));
              }
          });
    umm y = 0;
    auto visit = [&](auto f, umm vi, umm m, umm g = 0, const dyn<umm>& d = {}, umm pi = -1) -> void
    {
        if(m == 0)
        {
            if(g > y)
            {
                y = g;
                print("New highest: %\n", y);
            }
            return;
        }
        each(p[vi], [&](const auto& it)
             {
                 umm ni = find(v, it);
                 if(ni != pi) f(f, ni, m - 1, g, d, vi);
             });
        if(find(d, vi) == -1)
        {
            auto nd = d;
            nd.add(vi);
            f(f, vi, m - 1, g + (m - 1) * r[vi], nd, vi);
        }
    };
    
    visit(visit, find(v, "AA"_s), 30);
    print("Total pressure released: %\n", y);
}

void day17(cstr in)
{
    using point = sta<s64, 2>;
    dyn<sta<s64, 7>> g(umm(100000));
    dyn<dyn<point>> r;
    r.add(mdyn(point{ 0, 0 }, point{ 1, 0 }, point{ 2, 0 }, point{ 3, 0 }));
    r.add(mdyn(point{ 1, 0 }, point{ 0, 1 }, point{ 1, 1 }, point{ 2, 1 }, point{ 1, 2 }));
    r.add(mdyn(point{ 0, 0 }, point{ 1, 0 }, point{ 2, 0 }, point{ 2, 1 }, point{ 2, 2 }));
    r.add(mdyn(point{ 0, 0 }, point{ 0, 1 }, point{ 0, 2 }, point{ 0, 3 }));
    r.add(mdyn(point{ 0, 0 }, point{ 1, 0 }, point{ 0, 1 }, point{ 1, 1 }));
    s64 h = 0;
    s64 p = 0;
    s64 d = 0;
    for(umm i = 0; i < 1870 + 1575; i++)
    {
        auto a = r[i % size(r)];
        point c{ 2, p + 3 };
        while(true)
        {
            auto n = c;
            n[0] += in[d] == '<' ? -1 : 1;
            d = (d + 1) % (size(in) - 1);
            s64 b = 0;
            each(a, [&](auto it){ b = max(b, it[0]); });
            if(n[0] < 0 || n[0] + b >= size(g[0])) n = c;
            for(umm j = 0; j < size(a); j++)
            {
                auto t = n + a[j];
                if(g[t[1]][t[0]]) n = c;
            }
            c = n;
            n[1]--;
            if(n[1] < 0) n = c;
            for(umm j = 0; j < size(a); j++)
            {
                auto t = n + a[j];
                if(g[t[1]][t[0]]) n = c;
            }
            if(n == c) break;
            c = n;
        }
        for(umm j = 0; j < size(a); j++)
        {
            auto t = c + a[j];
            g[t[1]][t[0]] = 1;
            p = max(p, t[1] + 1);
        }
        bool row = true;
        for(umm j = 0; j < size(g[0]); j++) if(g[p - 1][j] == 0) row = false;
        if(row)
        {
            print("Spliting row at %, after % rocks, at input %\n", p, i, d);
            h += p;
            p = 0;
            g.resize(0);
            g.resize(umm(100000));
        }
    }
    print("Units: %, %\n", h, p);
}

int main()
{
    try
    {
        dstr in = filestr("day17.txt"_s);
        day17(in);
    }
    catch(const error& e)
    {
        print("Unhandled error: %\n", e.what());
    }
    return 0;
}
