@echo off
:: removing path first make sure we get the case right
set Path=
set Path=%ProgramFiles%\dotnet\;%WINDIR%;%WINDIR%\System32;%WINDIR%\System32\Wbem;%WINDIR%\System32\WindowsPowerShell\v1.0
set ComSpec=
set ComSpec=%WINDIR%\system32\cmd.exe 

for /f "tokens=1* delims==" %%a in ('set') do (
    if NOT [%%a] == [Path] (
        set %%a=
    )
)
set
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
