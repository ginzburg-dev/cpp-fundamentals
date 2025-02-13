#include "multifile_template_h.h"
#include <cassert>
#include <iostream>

int main()
{
    assert(max(1, 2) == 2);
    assert(max(2, 1) == 2);

    return 0;
}
