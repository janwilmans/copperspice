:: do not change the build target paths (causes stashed.io misses)
:: the ninja generator will use the default target platform of the 'Visual Studio Tools Command Prompt' it runs in.

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

:: set CMAKE_PREFIX_PATH=C:\copperspice\cmake\CopperSpice
:: -DWITH_WEBKIT=NO -DWITH_MYSQL_PLUGIN=NO

::-DCMAKE_INSTALL_PREFIX=install -DWITH_WEBKIT=NO

mkdir x64
mkdir x64\release
pushd x64\release
cmake -DCMAKE_INSTALL_PREFIX=install -DMSVC_TOOLSET_VERSION=142 -DCMAKE_BUILD_TYPE=RelWithDebInfo -G Ninja %SRC%
popd

mkdir x64\debug
pushd x64\debug
cmake -DCMAKE_INSTALL_PREFIX=install -DMSVC_TOOLSET_VERSION=142 -DCMAKE_BUILD_TYPE=Debug -G Ninja %SRC%
popd

@echo off
echo Compile using: (order of arguments is important!)
echo cmake --build x64\release
echo   or 
echo cmake --build x64\debug

pause
