@echo off

xcopy "extlib\*.dll"
Lets_Get_The_Aliens.exe
del "*.dll" /f /q
cmd /k