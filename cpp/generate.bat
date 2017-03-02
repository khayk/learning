:: Tool - 10, 11, 14, ...
:: Arch - 32 or 64
::
:: generate.bat [tool] [arch]

:: @todo: fix build issue for 32 bit application

@echo off

if "%tool%" neq "" goto include_vs_toolset

:detect_tool
if "%1" neq "" set tool=%1
if "%2" neq "" set arch=%2

if "%arch%" == "" set arch=64
if "%tool%" neq "" goto include_vs_toolset


:: tool is not specified, try to find latest available version of visual studio
if "%VS140COMNTOOLS%" neq "" (
    set tool=14
    goto include_vs_toolset
)


:: perform call for appropriate VSCOMNTOOLS
:include_vs_toolset

if "%toolset_included%" == "1" goto generate_project

if "%tool%" == "14" set comn_tools=%VS140COMNTOOLS%
if "%tool%" == "12" set comn_tools=%VS120COMNTOOLS%
if "%tool%" == "11" set comn_tools=%VS110COMNTOOLS%
if "%tool%" == "10" set comn_tools=%VS100COMNTOOLS%

if "%comn_tools" == "" goto error_unknown_tool

set arg=x86
set cmake_arch=
if "%arch%" == "64" (
    set arg=amd64
    set cmake_arch=Win64
)

echo VS%tool%0COMNTOOLS  : call "%comn_tools%..\..\VC\vcvarsall.bat" %arg%
call "%comn_tools%..\..\VC\vcvarsall.bat" %arg%
set toolset_included=1


:generate_project
echo Toolset         : %tool%
echo Architecture    : %arch%
echo CommonTools     : %comn_tools%

set source_dir=%~dp0
set build_dir=%source_dir%build\vs%tool%

if not exist "%build_dir%" (
    mkdir "%build_dir%"
)

pushd "%build_dir%" > NUL
if %errorlevel% == 1 goto error_build_dir
set build_dir=%CD%

echo Build directory : %build_dir%
echo CMake command   : cmake.exe -G "Visual Studio %tool% %cmake_arch%" "%source_dir%"

cmake.exe -G "Visual Studio %tool% %cmake_arch%" "%source_dir%"

popd > NUL

:: everything is ok
goto end

:error_unknown_tool
echo ERROR: unknown tool %tool%
goto end

:error_build_dir
echo ERROR: unable to create build directory

:end

