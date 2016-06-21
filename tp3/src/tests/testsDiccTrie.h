#include <string>
#include <iostream>

#include "../modulos/diccTrie.h"
#include "../mini_test.h"

namespace testsDiccTrie
{
    void constructor() {
        ASSERT(true);
    }

    void main(int, char**) {
        std::cout << "trie:" << std::endl;
        RUN_TEST( constructor );
    }
}
