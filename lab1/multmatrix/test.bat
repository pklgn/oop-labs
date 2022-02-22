@echo off
set PROGRAM="%~1"

rem common tests
%PROGRAM% input.txt input1.txt
if ERRORLEVEL 1 goto err
%PROGRAM% input.txt input4.txt
if ERRORLEVEL 1 goto err


rem tests for error
%PROGRAM% input1.txt input2.txt
if NOT ERRORLEVEL 1 goto err
%PROGRAM% input1.txt input3.txt
if NOT ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1