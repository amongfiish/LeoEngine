@echo off

REM THIS ONLY HAS TO BE RUN BEFORE THE FIRST BUILD

Powershell -executionpolicy remotesigned -File ..\..\lib\sdl_image\external\Get-GitModules.ps1
Powershell -executionpolicy remotesigned -File ..\..\lib\sdl_mixer\external\Get-GitModules.ps1
Powershell -executionpolicy remotesigned -File ..\..\lib\sdl_ttf\external\Get-GitModules.ps1

