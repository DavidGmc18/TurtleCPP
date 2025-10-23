@echo off
SET TESTNAME=%1
IF "%TESTNAME%"=="" SET TESTNAME=test

SET ROOT=%~dp0

clang++ "%ROOT%\test\%TESTNAME%.cpp" ^
    -I"%ROOT%\include" ^
    -I"%USERPROFILE%\vcpkg\installed\x64-windows\include" ^
    -L"%ROOT%\build" -lturtle ^
    "%USERPROFILE%\vcpkg\installed\x64-windows\lib\glfw3dll.lib" ^
    -lopengl32 -lgdi32 -pthread ^
    -o "%ROOT%\test\%TESTNAME%.exe"

IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed
    exit /b %ERRORLEVEL%
)

SET PATH=%PATH%;%ROOT%\build;
"%ROOT%\test\%TESTNAME%.exe"

del "%ROOT%\test\%TESTNAME%.exe"