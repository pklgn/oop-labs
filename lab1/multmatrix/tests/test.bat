@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%\output.txt"
set DIR=%~p0

rem common tests
%PROGRAM% %DIR%\inputA.txt %DIR%\inputB.txt > %OUTPUT%
fc.exe %OUTPUT% %DIR%\outputAxB.txt >nul
if ERRORLEVEL 1 goto err

rem identity matrix
%PROGRAM% %DIR%\inputB.txt %DIR%\inputB.txt > %OUTPUT%
fc.exe %OUTPUT% %DIR%\outputBxB.txt >nul 
if ERRORLEVEL 1 goto err

rem wrong element
%PROGRAM% %DIR%\inputB.txt %DIR%\inputC.txt > %OUTPUT%
fc.exe %OUTPUT% %DIR%\outputBxC.txt >nul 
if ERRORLEVEL 1 goto err

rem wrong matrix
%PROGRAM% %DIR%\inputB.txt %DIR%\inputD.txt > %OUTPUT%
fc.exe %OUTPUT% %DIR%\outputBxD.txt >nul 
if ERRORLEVEL 1 goto err

rem double matrix
%PROGRAM% %DIR%\inputB.txt %DIR%\inputE.txt > %OUTPUT%
fc.exe %OUTPUT% %DIR%\outputBxE.txt >nul 
if ERRORLEVEL 1 goto err


echo All tests have been successfully passed!
exit 0

:err
echo Program testing failed
exit 1