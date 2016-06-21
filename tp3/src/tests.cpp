// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
#include <iostream>

#include "Driver.h"
#include "mini_test.h"

#include "tests/testsDato.h"
#include "tests/testsDiccLog.h"
#include "tests/testsEjemplo.h"

int main(int argc, char **argv) {
    std::cout << "............." << std::endl
              << "Running tests" << std::endl
              << "'''''''''''''" << std::endl;
    testsDato::main(argc, argv);
    testsDiccLog::main(argc, argv);
    testsEjemplo::main(argc, argv);
    std::cout << ".........." << std::endl
              << "Tests done" << std::endl
              << "''''''''''" << std::endl;

    return 0;
}

