@echo off
set PROGRAM="%~1"

rem simple tests
%PROGRAM% 16 10 -FFFFFF
%PROGRAM% 16 10 1FFFFFFF

rem vice versa
%PROGRAM% 36 2 ABBA
rem back
%PROGRAM% 2 36 1010101110111010

rem overflow and not 
%PROGRAM% 16 10 FFFFFFFF
%PROGRAM% 16 10 -FFFFFFFF

rem err params
%PROGRAM% 1 37 ABCD
%PROGRAM% 9 2 ABCD
%PROGRAM% 10 G FFFFFFFF
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1