@echo off

mkdir G:\Win32-SDLGame\Build
pushd G:\Win32-SDLGame\Build

rem Put all the compile stuff here
g++ -Wall G:\Win32-SDLGame\Project-Files\HelloSDL.cpp -o HelloSDL -IC:\SDL2\x86_64-w64-mingw32\include\SDL2\ -LC:\SDL2\x86_64-w64-mingw32\lib -lSDL2 -lSDL2main -lmingw32 
popd
