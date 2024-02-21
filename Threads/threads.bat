cd C:\Users\79085\source\repos\cpp_study\Threads\build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release

chcp 1251
@echo off
echo _
echo Thread initialization approachs C++
echo _
.\Release\threads_init.exe
pause
.\Release\threads_join.exe
pause
.\Release\threads_mutex.exe
pause