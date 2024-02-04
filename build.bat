@echo off
cls

:: ***********************************************************************
   rem Batch file for compiling Raylib and/or Raygui applications
:: ***********************************************************************

:Initialization
	SET "RAYLIB_DIR=C:\raylib"
	SET "CURRENT_DIR=%cd%"

	SET "INPUT_FILE=%1"
	SET "OUTPUT_FILE=%2"
	SET "INCLUDE_FILES= -I %cd% -I C:/raylib/raylib/src"

	SET "COMPILER= C:\mingw64\bin\g++.exe"
	SET "CFLAGS=%RAYLIB_DIR%\raylib\src\raylib.rc.data -Wall -std=c++17 -D_DEFAULT_SOURCE -Wno-missing-braces"
	SET "LDFLAGS= -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm"
	SET "EXTRAFLAGS="

	IF /I "%3"=="Release" SET EXTRAFLAGS=%EXTRAFLAGS% -O3


:Main
	echo(
	echo ^> Removing Previous Build
	echo ----------------------------
	IF EXIST "%1.exe" del /F "%1.exe"

	echo(
	echo ^> Compiling Program
	echo ----------------------------
	%COMPILER% -o "%OUTPUT_FILE%" *.cpp %INCLUDE_FILES% %CFLAGS% %LDFLAGS% %EXTRAFLAGS%