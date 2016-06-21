#include <string>
#include <iostream>

#include "../modulos/diccLog.h"

namespace testsDiccLog
{
    void constructor()
    {
        tp3::DiccLog<int, int> dicc;
    }

    void main(int argc, char **argv)
    {
        std::cout << "diccLog:" << std::endl;  
        RUN_TEST( constructor );
    }
}
