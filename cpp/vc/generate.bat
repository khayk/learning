:: Tool - 10, 11, 14, 15 ...
:: Arch - 32 or 64
::
:: generate.bat [tool] [arch]

:: @todo: fix build issue for 32 bit application

@echo off

if "%1" neq "" set tool=%1
if "%2" neq "" set arch=%2

if "%arch%" == "" set arch=64
if "%tool%" neq "" goto detect_vs_version


:: tool is not specified, use default value 14
set tool=14


:detect_vs_version
if "%tool%" == "15" set studio_name=2017
if "%tool%" == "14" set studio_name=2015
if "%tool%" == "12" set studio_name=2013
if "%tool%" == "11" set studio_name=2012
if "%tool%" == "10" set studio_name=2010

set cmake_arch=
if "%arch%" == "64" set cmake_arch=Win64

:generate_project
echo Toolset         : %tool%
echo Architecture    : %arch%

set source_dir=%~dp0../
set build_dir=%source_dir%build\vs%tool%-x%arch%

if not exist "%build_dir%" (
    mkdir "%build_dir%"
)

pushd "%build_dir%" > NUL
if %errorlevel% == 1 goto error_build_dir
set build_dir=%CD%

set cmake_command=cmake.exe -G ^"Visual Studio %tool% %studio_name%
if "%cmake_arch%" neq "" (
    set "cmake_command=%cmake_command% %cmake_arch%"
)
:: add  -DCPP_RUNTIME:STRING=STATIC  to smake_command to link with msvc static libs
set "cmake_command=%cmake_command%^" ^"%source_dir%^""

echo Build directory : %build_dir%
echo CMake command   : %cmake_command%

:: executre cmake command
%cmake_command%

popd > NUL

if %errorlevel% == 1 goto wait_response

:: everything is ok
goto end

:error_build_dir
echo ERROR: unable to create build directory
goto wait_response

:wait_response
pause

:end
