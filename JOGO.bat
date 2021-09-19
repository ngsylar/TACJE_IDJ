@echo off

xcopy "extlib\*.dll"
JOGO.exe
del "SDL2.dll" /f /q
del "SDL2_image.dll" /f /q
del "SDL2_mixer.dll" /f /q
del "SDL2_ttf.dll" /f /q
del "libFLAC-8.dll" /f /q
del "libfreetype-6.dll" /f /q
del "libgcc_s_dw2-1.dll" /f /q
del "libjpeg-9.dll" /f /q
del "libmodplug-1.dll" /f /q
del "libmpg123-0.dll" /f /q
del "libogg-0.dll" /f /q
del "libopus-0.dll" /f /q
del "libopusfile-0.dll" /f /q
del "libpng16-16.dll" /f /q
del "libstdc++-6.dll" /f /q
del "libtiff-5.dll" /f /q
del "libvorbis-0.dll" /f /q
del "libvorbisfile-3.dll" /f /q
del "libwebp-7.dll" /f /q
del "zlib1.dll" /f /q