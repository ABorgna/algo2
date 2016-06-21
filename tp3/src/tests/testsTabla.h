#include <string>
#include <iostream>

#include "../modulos/tabla.h"
#include "../mini_test.h"

namespace testsTabla
{
    void constructor() {
        ASSERT(true);
    }

    void main(int, char**) {
        std::cout << "******** tabla *********" << std::endl;
        RUN_TEST( constructor );
    }
}
