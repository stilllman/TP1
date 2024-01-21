# TestCompil

## Setup

### CMake
* Download CMake from https://cmake.org/download/
* Install it
  * Select "Add CMake to the system PATH for the current user" for ease of use

### QT
* Download Qt from https://www.qt.io/download-qt-installer-oss?utm_referrer=https%3A%2F%2Fwww.qt.io%2Fdownload-open-source
* Install it
  * Installation personnalisée
  * Choose a MinGW version
  * Choose cmake if not alreay installed

## Configuration
```console
mkdir build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
cmake --build .
```

## Run
```console
ctest => one test successful
.\bin\Debug\TestCompil.exe => UI shows
```
