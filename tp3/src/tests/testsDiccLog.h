#include <string>
#include <iostream>

#include "../modulos/diccLog.h"
#include "../mini_test.h"

namespace testsDiccLog
{
    void constructor()
    {
        tp3::DiccLog<int, int> dicc;
    }

    void main(int, char **)
    {
        std::cout << "******** diccLog *******" << std::endl;
        RUN_TEST( constructor );
    }
}
