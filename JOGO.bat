@echo off

xcopy "extlib\*.dll"
JOGO.exe
del "*.dll" /f /q
cmd /k