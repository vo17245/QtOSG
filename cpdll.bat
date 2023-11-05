set sourceFolder=dependencies\OpenSceneGraph-3.6.5-VC2022-64-Debug-2023-01\bin
set sourceFolder1=dependencies\OpenSceneGraph-3.6.5-VC2022-64-Debug-2023-01\bin\osgPlugins-3.6.5
set destinationFolder=build\Debug

if not exist "%destinationFolder%" (
    mkdir "%destinationFolder%"
)

for %%i in ("%sourceFolder%\*.dll") do (
    copy "%%i" "%destinationFolder%"
)
for %%i in ("%sourceFolder%\*.pdb") do (
    copy "%%i" "%destinationFolder%"
)
for %%i in ("%sourceFolder1%\*.dll") do (
    copy "%%i" "%destinationFolder%"
)
for %%i in ("%sourceFolder1%\*.pdb") do (
    copy "%%i" "%destinationFolder%"
)

if exist "build\Debug\QtOSG.exe" (
    D:\opt\Qt\5.14.2\5.14.2\msvc2017_64\bin\windeployqt.exe build\Debug\QtOSG.exe
)

if exist "build\Release\QtOSG.exe" (
    D:\opt\Qt\5.14.2\5.14.2\msvc2017_64\bin\windeployqt.exe build\Release\QtOSG.exe
)
pause