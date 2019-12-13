:: Batch build script
:: Project    - Vess A6x00
:: Compiler   - Visual Studio 2012 C#
::
:: This script is created by Yue Li, 2018.10.10.
:: 


:: Script start here

::echo off

:: Search Visual Studio in "Program Files"
SET DEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat"
if exist %DEVENV% goto SetEnv

:: Search Visual Studio in "Program Files (x86)"
SET DEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat"
if exist %DEVENV% goto SetEnv

echo Cannot find the Visual Studio 2017
goto QUIT

:SetEnv
cd %~d0\%~p0
call %DEVENV% x64
MSBuild.exe Enclosure_Monitor.sln /t:Clean,Build /p:Configuration=Release /p:Platform="x64"

:QUIT
IF NOT "%1" == "NOPAUSE" (
    PAUSE
) ELSE (
    EXIT
)
echo on
