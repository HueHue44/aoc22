@echo off

where /q cl || (
  echo ERROR: "cl" not found
  exit /b 1
)

call cl /std:c++20 /EHsc /W4 /Zi /I ../peak %* main.cpp User32.lib Gdi32.lib Shell32.lib ws2_32.lib
