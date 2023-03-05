@echo off
chcp 65001
echo tests starting
SET PROGRAM="%~1"
SET OUT="%TEMP%\out.txt"

%PROGRAM% 10 10 10 > %OUT% || goto err
fc %OUT% 10-10-10.txt || goto err
echo test 1 passed

%PROGRAM% 36 2 ZZZ > %OUT% || goto err
fc %OUT% 36-2-ZZZ.txt || goto err
echo test 2 passed

%PROGRAM% 37 2 ZZZ > %OUT% || goto err
fc %OUT% incorrect-number-system.txt || goto err
echo test 3 passed

%PROGRAM% 35 2 A!A > %OUT% || goto err
fc %OUT% incorrect-char.txt || goto err
echo test 4 passed

%PROGRAM% 35 2 Z > %OUT% || goto err
fc %OUT% digit-of-another-number-system.txt || goto err
echo test 5 passed

%PROGRAM% 36 2 ZZZZZZZZZZZZZZZ > %OUT% || goto err
fc %OUT% overflow.txt || goto err
echo test 6 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1