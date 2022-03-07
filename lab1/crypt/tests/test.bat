@echo off
set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"
set DIR=%~dp0

rem simple test
%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted.txt 128
fc.exe %DIR%B_encrypted_check.txt %TEMP%\B_encrypted.txt >nul 
if ERRORLEVEL 1 goto err

rem key value is out of range
%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted_257.txt 257 > %OUTPUT%
fc.exe %DIR%Out_of_range.txt %OUTPUT% >nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted.txt -1 > %OUTPUT%
fc.exe %DIR%Out_of_range.txt %OUTPUT% >nul
if ERRORLEVEL 1 goto err

rem invalid key value
%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted.txt aa > %OUTPUT%
fc.exe %DIR%Invalid_key_value_check.txt %OUTPUT% >nul  
if ERRORLEVEL 1 goto err

%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted.txt "" > %OUTPUT%
fc.exe %DIR%Invalid_key_value_check.txt %OUTPUT% >nul  
if ERRORLEVEL 1 goto err

rem wrong argument count
%PROGRAM% crypt %DIR%B.txt %TEMP%\B_encrypted.txt > %OUTPUT%
fc.exe %DIR%Wrong_argument_count.txt %OUTPUT% >nul
if ERRORLEVEL 1 goto err

rem invalid mode name
%PROGRAM% deecrypt %DIR%B.txt %TEMP%\B_encrypted.txt 128 >%OUTPUT%
fc.exe %DIR%Invalid_program_mode.txt %OUTPUT% >nul 
if ERRORLEVEL 1 goto err

rem vice versa
%PROGRAM% crypt %DIR%tiny_text.txt %TEMP%\tiny_text.txt 128
if ERRORLEVEL 1 goto err 
%PROGRAM% decrypt %TEMP%\tiny_text.txt %TEMP%\new_tiny_text 128
if ERRORLEVEL 1 goto err
fc.exe %DIR%tiny_text.txt %TEMP%\new_tiny_text >nul
if ERRORLEVEL 1 goto err 

rem encrypt executable
%PROGRAM% crypt %PROGRAM% %TEMP%\program.txt 42
if ERRORLEVEL 1 goto err 
%PROGRAM% decrypt %TEMP%\program.txt %TEMP%\newCrypt.exe 42
if ERRORLEVEL 1 goto err
%TEMP%\newCrypt.exe crypt %DIR%tiny_text.txt %TEMP%\tiny_text1.txt 128
if ERRORLEVEL 1 goto err 
%TEMP%\newCrypt.exe decrypt %TEMP%\tiny_text1.txt %TEMP%\new_tiny_text1.txt 128
if ERRORLEVEL 1 goto err
fc.exe %DIR%tiny_text.txt %TEMP%\new_tiny_text1.txt >nul
if ERRORLEVEL 1 goto err 
                        
echo All tests have been successfully passed!
exit 0

:err
echo Program testing failed
exit 1
