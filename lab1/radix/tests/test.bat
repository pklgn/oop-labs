@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"
set DIR=%~dp0

rem simple tests
%PROGRAM% 16 10 -FFFFFF > %OUTPUT%
fc.exe %DIR%-FFFFFF.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err
%PROGRAM% 16 10 1FFFFFFF > %OUTPUT%
fc.exe %DIR%1FFFFFFF.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

::vice versa
::convert from 36 number system to 2 number system
%PROGRAM% 36 2 ABBA  > %OUTPUT%
fc.exe %DIR%ABBA.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err
rem convert the exact number back
%PROGRAM% 2 36 1110101011111000110 > %OUTPUT%
fc.exe %DIR%1110101011111000110.txt %OUTPUT% > nul 
if ERRORLEVEL 1 goto err

rem check the overflow of a positive number 
%PROGRAM% 16 10 80000000  > %OUTPUT%
fc.exe %DIR%INT_MAX_OVERFLOW.txt %OUTPUT% > nul 
if ERRORLEVEL 1 goto err
rem check the absence of the overflow of a INT_MAX number 
%PROGRAM% 16 10 7FFFFFFF  > %OUTPUT%
fc.exe %DIR%INT_MAX.txt %OUTPUT% > nul 
if ERRORLEVEL 1 goto err


rem check the absence of the overflow of a INT_MIN number  
%PROGRAM% 16 10 -80000000  > %OUTPUT%
fc.exe %DIR%INT_MIN.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err
rem check the overflow of a negative number 
%PROGRAM% 16 10 -80000001  > %OUTPUT%
fc.exe %DIR%INT_MIN_OVERFLOW.txt %OUTPUT% > nul 
if ERRORLEVEL 1 goto err

rem error params
%PROGRAM% 1 37 ABCD  > %OUTPUT%
fc.exe %DIR%ABCD_notation.txt %OUTPUT% > nul 
if ERRORLEVEL 1 goto err

rem another simple test
%PROGRAM% 9 2 ABCD  > %OUTPUT%
fc.exe %DIR%ABCD.txt %OUTPUT% > nul  
if ERRORLEVEL 1 goto err


echo All tests have been successfully passed!
exit 0

:err
echo Program testing failed
exit 1