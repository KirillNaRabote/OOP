set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

set OUT="%TEMP%\out.txt"

%PROGRAM% fox.txt %OUT% bird cat || goto err
fc.exe %OUT% fox.txt || goto err

%PROGRAM% fox.txt %OUT% dog cat || goto err
fc.exe %OUT% fox-replace-dog-with-cat.txt || goto err

%PROGRAM% ma.txt %OUT% ma mama || goto err
fc.exe %OUT% ma-replace-ma-with-mama.txt || goto err

%PROGRAM% empty.txt %OUT% "" "" || goto err
fc.exe %OUT% empty-replace-nothing-with-nothing.txt || goto err

%PROGRAM% empty.txt %OUT% adr 123 || goto err
fc.exe %OUT% empty-replace-adr-with-123.txt || goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1