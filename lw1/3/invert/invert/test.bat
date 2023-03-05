@echo off
chcp 65001
echo tests starting
SET PROGRAM="%~1"
SET OUT="%TEMP%\out.txt"

%PROGRAM% testMatrix1.txt > %OUT% || goto err
fc %OUT% testMatrixOut1.txt || goto err
echo test 1 passed

%PROGRAM% testMatrix2.txt > %OUT% || goto err
fc %OUT% testMatrixOut2.txt || goto err
echo test 2 passed

%PROGRAM% testMatrix3.txt > %OUT% || goto err
fc %OUT% testMatrixOut3.txt || goto err
echo test 3 passed

%PROGRAM% testMatrix4.txt > %OUT% || goto err
fc %OUT% testMatrixOut4.txt || goto err
echo test 4 passed

%PROGRAM% testMatrix5.txt > %OUT% || goto err
fc %OUT% testMatrixOut5.txt || goto err
echo test 5 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1