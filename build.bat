@echo off

set batchDir=%~dp0
set config=%1
set runPremake=1

if "%1"=="clean" (
   if exist %batchDir%\bin (
       rmdir /s /q  %batchDir%\bin
       echo deleted .\bin\
   )
   if exist %batchDir%\build (
       rmdir /s /q %batchDir%\build
       echo deleted .\build\
   )
   
   goto :eof
)

rem check if subcommand is in 1st argument
if "%1"=="help" (
   echo Usage: build.bat ^<Build^|Release^|All> [subcommand]
   echo.
   echo Subcommands:
   echo        help       Prints the usage.
   echo        run        Runs the the first .exe file found in .\bin\^<Debug^|Release^>.
   echo        srun       Same as run but runs in a new process.
   echo        clean      Removes .\bin\ and .\build\ if they exist.
   echo        dir        Opens the directory of the built program.
   echo.
   echo NOTE:if only 'run' subcommand is provided with no config the program will run without building.
   goto :eof
)


if "%1"=="run" (
    set config=Debug
    goto :run
)

if "%1"=="srun" (
    set config=Debug
    goto :srun
)

if "%1"=="dir" (
    set config=Debug
    goto :dir
)

rem run premake5
if "%runPremake%"=="1" (
   echo.
   echo ^<=== Running Premake5 ===^>
   echo.
   premake5 --file=%batchDir%\premake5.lua vs2022
)

rem default condig is Debug
if "%config%"=="" (
    set config=Debug
)

echo.
echo ^<=== Building %config% ===^>
echo.


if "%config%"=="All" (
    for %%F in (%batchDir%build\*) do (
       if "%%~xF"==".sln" (
	   msbuild -p:configuration=Debug -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m %batchDir%build\%%~nF.sln
	   msbuild -p:configuration=Release -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m %batchDir%build\%%~nF.sln
       )
    )
    goto :skipBuildOne
)

for %%F in (%batchDir%build\*) do (
    if "%%~xF"==".sln" (
        msbuild -p:configuration=%config% -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m %batchDir%build\%%~nF.sln
    )
)
:skipBuildOne

if not "%errorlevel%"=="0" ( exit %errorlevel% )

if "%2"=="" (
    goto :eof
)

rem check if subcommand is in 2nd argument
if "%2"=="run" (
    goto :run
)

if "%2"=="srun" (
    goto :srun
)

if "%2"=="dir" (
    goto :dir
)

:run
if not exist %batchDir%bin (
    echo ERROR: executable not found!
    echo HINT: try to build once before running!
    exit 1
)
if "%config%"=="All" (
   echo ERROR: you can't run after building all the configurations!
   echo HINT: try to only build one and run
   exit 1
)

cd %batchDir%bin\%config%\

for %%F in (*.*) do (
    if "%%~xF"==".exe" (
	echo.
	echo ^<=== RUNNING %%~nxF ===^>
	echo.

	%%F
    )
)
if not "%errorlevel%"=="0" ( exit %errorlevel% ) 

goto :eof

:srun
if not exist %batchDir%bin (
    echo ERROR: executable not found!
    echo HINT: try to build once before running!
    exit 1
)
cd %batchDir%bin\%config%\

for %%F in (*.*) do (
    if "%%~xF"==".exe" (
	echo.
	echo ^<=== RUNNING %%~nxF ===^>
	echo.

	start %%F
    )
)
goto :eof

:dir
start %batchDir%bin\%config%\
goto :eof
