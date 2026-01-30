@echo off
cd ..
cd src
for %%f in (*) do (
    if /i not "%%~xf"==".cpp" (
        if /i not "%%~xf"==".h" (
            if /i not "%%~xf"==".bat" (
                    echo Deleting: %%f
                    del "%%f" /q
            )
        )
    )
)
echo.
echo Done! Only .cpp, .h, and .bat files remain.
dir /b
pause