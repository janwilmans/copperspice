setlocal

:: make path local because vcvarsall.bat polutes it
setlocal Path=%PATH%

set SRC=%cd%
set COM_BUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"
set PRO_BUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat"
set ENT_BUILD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"

if exist %COM_BUILD% (
  call %COM_BUILD% x64
) 

if exist %PRO_BUILD% (
  call %PRO_BUILD% x64
) 

if exist %ENT_BUILD% (
  call %ENT_BUILD% x64
) 

cmd.exe
