#define DYNA_INT
#include "iDynA.h"

int main(void)
{
    DynA *d = &DynAs[0];
    d = d->init(10);

    int val;

    d->print_all(d);

    d->put(1);


    /*
    d->put(d, 2);
    d->put(d, 3);
    d->print_all(d);
    val = geti(d, 1);
    dbg("val: %d", val);
    val = geti(d, 2);
    dbg("deleted: %d", val);
    d->put(d, 199);

    d->deinit(d);
    */
    return 0;
}
