# Kompilacja:
1. Aby skompilowac program, należy mieć zainstalowane programy:
- `clang`, lub inny kompilator języka C++, obsługujący standard C++11
- `GNU make` 

Kompilacja zostaje wtedy wykonana przez wpisanie komendy `make`, będąc w katalogu z kodem programu. Można również wywołać plik shell o nazwie `test.sh` zawarty w katalogu z kodem programu.


2. W przypadku braku programu `make`:

Program jest napisany w jezyku C++, zgodny ze standardem c++11, dlatego nalezy upewnic się, ze kompilator pracuje zgodnie z tym standardem. Przykladowo na moim systemie kompilacja zachodzi przez wykorzystanie komendy:

`clang++ -g -std=c++11 *.cpp`

analogicznie dla GCC:

`g++ -g -std=c++11 *.cpp`

Kompilacja oraz dzialanie zostaly przetestowana dla kompilatorow clang++ oraz g++(GNU Compiler Collection), na systemie Ubuntu w konfiguracji WSL(Windows Subsystem Linux), na systemie Windows 10. Jednak program korzysta tylko z bibliotek standardowych C oraz C++, dlatego raczej nie powinno byc problemow zwiazanych z kompilowaniem.

Testowane wersje kompilatorow:
* `g++ -v` : `gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)`
* `clang++ -v` : 
`clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin`

