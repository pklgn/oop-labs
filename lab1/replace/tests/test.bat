@echo off
set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

::ѕроверка на неверное количество аргументов
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% tests\book.txt "%DIR%\output_book.txt" star ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe tests\book.txt "%DIR%\output_book.txt" >nul

%PROGRAM% tests\empty_file.txt "%DIR%\output_empty_file.txt" test ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe tests\empty_file.txt "%DIR%\output_empty_file.txt"

%PROGRAM% tests\small_text.txt "%DIR%\output_small_text.txt" re ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe tests\small_text.txt "%DIR%\output_small_text.txt"

%PROGRAM% tests\small_number.txt "%DIR%\output_simple_example.txt" 1231234 ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe tests\small_number.txt "%DIR%\output_simple_example.txt"

%PROGRAM% tests\long_string.txt "%DIR%\output_very_long_string.txt" a bb
if ERRORLEVEL 1 goto err
fc.exe tests\long_string.txt "%DIR%\output_very_long_string.txt" >nul

%PROGRAM% tests\small_text.txt "%DIR%\output_small_text.txt" "" ABRACADABRA
if ERRORLEVEL 1 goto err
fc.exe tests\small_text.txt "%DIR%\output_small_text.txt" 


echo OK
exit 0

:err
echo Program testing failed
exit 1