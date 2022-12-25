@echo off

where /q cl && (
    cl /std:c++20 /EHsc /W4 /Zi /I../peak %* main.cpp User32.lib Gdi32.lib Shell32.lib ws2_32.lib
    exit /b
) || where /q g++ && (
    g++ -std=c++20 -msse4.1 -I../peak %* main.cpp -lgdi32 -lws2_32 -o main
    exit /b
) || (
    echo Error: found no suitable compiler in PATH. Checked for cl and g++.
    exit /b 1
)
