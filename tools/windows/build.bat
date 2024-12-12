cd ..\..

cmake . -B build
cd build
"%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" LeoEngine.vcxproj /p:configuration=debug /p:platform=x64

