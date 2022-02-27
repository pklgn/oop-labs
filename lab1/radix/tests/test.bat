@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"

rem simple tests
%PROGRAM% 16 10 -FFFFFF > %OUTPUT%
fc.exe -FFFFFF.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err
%PROGRAM% 16 10 1FFFFFFF > %OUTPUT%
fc.exe 1FFFFFFF.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err


rem vice versa
%PROGRAM% 36 2 ABBA  > %OUTPUT%
fc.exe ABBA.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem back
%PROGRAM% 2 36 1110101011111000110 > %OUTPUT%
fc.exe 1110101011111000110.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err



rem overflow and not 
%PROGRAM% 16 10 80000000  > %OUTPUT%
fc.exe INT_MAX_OVERFLOW.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err
 
%PROGRAM% 16 10 7FFFFFFF  > %OUTPUT%
fc.exe INT_MAX.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err


rem overflow and not 
%PROGRAM% 16 10 -80000000  > %OUTPUT%
fc.exe INT_MIN.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 -80000001  > %OUTPUT%
fc.exe INT_MIN_OVERFLOW.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err


rem err params
%PROGRAM% 1 37 ABCD  > %OUTPUT%
fc.exe ABCD_notation.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

%PROGRAM% 9 2 ABCD  > %OUTPUT%
fc.exe ABCD.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err


echo OK
exit 0

:err
echo Program testing failed
exit 1