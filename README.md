# TP1

## Configuration
```console
mkdir build_debug
cd build_debug
# Les étudiants sont sous windows ? T'aurais pas meilleur compte de laisser le générateur par défaut ?
# Cela dit s'ils sont windows le générateur par défaut ça va être VS et t'as ptêtre pas envie de
# devoir gérer plusieurs toolchains.
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ..
cmake --build .
```

## Run
```console
ctest => one test successful
.\bin\Debug\TestCompil.exe => UI shows
```
