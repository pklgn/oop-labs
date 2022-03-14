@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"
set ERROR_OUTPUT="%TEMP%/error_output.txt"
set DIR=%~dp0

rem simple test
%PROGRAM% %DIR%example.txt %OUTPUT%
fc.exe %DIR%check_example.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem almost simple test with a start point out of borders
%PROGRAM% %DIR%start_point_out.txt %OUTPUT%
fc.exe %DIR%check_start_point_out.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem frame with a MAX_POS x MAX_POS dimensions
%PROGRAM% %DIR%max_pos.txt %OUTPUT%
fc.exe %DIR%check_max_pos.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem frame with a MAX_POS x MAX_POS dimensions and extra symbols
%PROGRAM% %DIR%max_pos_overflow.txt %OUTPUT%
fc.exe %DIR%check_max_pos_overflow.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem empty file
%PROGRAM% %DIR%empty_file.txt %OUTPUT%
fc.exe %DIR%check_empty_file.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem invalid arguments count
%PROGRAM% %DIR%empty_file.txt > %ERROR_OUTPUT%
fc.exe %DIR%check_invalid_arguments_count.txt %ERROR_OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem invalid map element
%PROGRAM% %DIR%invalid_map_element.txt %OUTPUT% > %ERROR_OUTPUT%
fc.exe %DIR%check_invalid_map_element.txt %ERROR_OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem complex form test
%PROGRAM% %DIR%complex_form.txt %OUTPUT%
fc.exe %DIR%check_complex_form.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem dd extra start point in the same figure
%PROGRAM% %DIR%several_start_point.txt %OUTPUT%
fc.exe %DIR%check_several_start_point.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

echo All tests have been successfully passed!
exit 0

:err
echo Program testing failed
exit 1

