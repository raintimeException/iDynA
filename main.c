#include "iDynA.h"

int main(void)
{
    DynA *d = init(0);
    int val;

    put(d, 1);
    put(d, 2);
    put(d, 3);
    print_all(d);
    val = geti(d, 1);
    dbg("val: %d", val);
    val = geti(d, 2);
    dbg("deleted: %d", val);
    put(d, 199);
    print_all(d);

    deinit(d);
    return 0;
}
