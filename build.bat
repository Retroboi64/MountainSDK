@echo off

cd build

cmake ..
rmdir /s /q build
cmake -S . -B build -G "Visual Studio 17 2022" 
cmake --build build --config Release

cd ..
pause