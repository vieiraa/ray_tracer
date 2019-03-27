@ECHO OFF

MKDIR build

DEL build\CMakeCache.txt

cd build

cmake .. -G "Visual Studio 15 2017" -A x64
