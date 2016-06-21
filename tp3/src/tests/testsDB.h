#include <string>
#include <iostream>

#include "../modulos/db.h"
#include "../mini_test.h"

namespace testsDB
{
    void constructor() {
        ASSERT(true);
    }

    void main(int, char**) {
        std::cout << "DB:" << std::endl;
        RUN_TEST( constructor );
    }
}
