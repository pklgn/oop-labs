@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%\output.txt"

rem common tests
%PROGRAM% tests\inputA.txt tests\inputB.txt > %OUTPUT%
fc.exe %OUTPUT% tests\outputAxB.txt >nul 
if ERRORLEVEL 1 goto err

rem identity matrix
%PROGRAM% tests\inputB.txt tests\inputB.txt > %OUTPUT%
fc.exe %OUTPUT% tests\outputBxB.txt >nul
if ERRORLEVEL 1 goto err

rem wrong element
%PROGRAM% tests\inputB.txt tests\inputC.txt > %OUTPUT%
fc.exe %OUTPUT% tests\outputBxC.txt >nul
if ERRORLEVEL 1 goto err

rem wrong matrix
%PROGRAM% tests\inputB.txt tests\inputD.txt > %OUTPUT%
fc.exe %OUTPUT% tests\outputBxD.txt >nul
if ERRORLEVEL 1 goto err

rem double matrix
%PROGRAM% tests\inputB.txt tests\inputE.txt > %OUTPUT%
fc.exe %OUTPUT% tests\outputBxE.txt >nul
if ERRORLEVEL 1 goto err



echo OK
exit 0

:err
echo Program testing failed
exit 1