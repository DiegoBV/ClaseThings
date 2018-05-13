@echo off
REM place this script in the same folder as your assets
REM edit to match your exe (beware of blank spaces in path)

start cmd /k %cd%\..\bin\HolaSDLDebug.exe server 2000
start cmd /k %cd%\..\bin\HolaSDLDebug.exe client localhost 2000

REM quick hack to wait a little(as the random seed would be the same)
ping 127.0.0.1 -n 3 > nul
start cmd /k %cd%\..\bin\HolaSDLDebug.exe client localhost 2000