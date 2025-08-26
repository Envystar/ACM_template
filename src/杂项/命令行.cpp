********** bat **********
@echo off
g++ %1.cpp -std=c++20 -O2 -Wall -o %1 -D_GLIBCXX_DEBUG
.\%1 < in.txt > out.txt
@REM type out.txt
*************************

********** sh *********** chmod +x
#!/bin/bash
g++ -std=c++20 -O2 -Wall "$1.cpp" -o "$1" -D_GLIBCXX_DEBUG
./"$1" < in.txt > out.txt
cat out.txt
*************************

********** sh *********** chmod +x
while true; do
    ./gen > 1.in
    ./std < 1.in > std.out
    ./my < 1.in > my.out
    if diff my.out std.out; then
        echo ac
    else
        echo wa
    break
    fi
done
*************************

********** bat **********
@echo off
:loop
    gen.exe > 1.in
    std.exe < 1.in > std.out
    my.exe < 1.in > my.out
    fc my.out std.out > nul
    if %errorlevel%==0 (
        echo ac
        goto loop
    ) else (
        echo wa
        goto :eof
    )
*************************