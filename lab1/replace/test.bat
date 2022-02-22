@echo off
set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% input.txt "%DIR%\output.txt" 1231234 ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe input.txt "%DIR%\output.txt"

%PROGRAM% input1.txt "%DIR%\output1.txt" test ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe input1.txt "%DIR%\output1.txt"

%PROGRAM% input3.txt "%DIR%\output3.txt" "" ""
if ERRORLEVEL 1 goto err
fc.exe input3.txt "%DIR%\output3.txt"

%PROGRAM% input2.txt "%DIR%\output2.txt" star ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe input2.txt "%DIR%\output2.txt" >nul

%PROGRAM% input3.txt "%DIR%\output3.txt" workd ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe input3.txt "%DIR%\output3.txt" >nul

%PROGRAM% input4.txt "%DIR%\output4.txt" re ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe input4.txt "%DIR%\output4.txt"


echo OK
exit 0

:err
echo Program testing failed
exit 1