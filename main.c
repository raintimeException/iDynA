#define TYPE double
#include "iDynA.h"

int main(void)
{
    DynA *d = GIVE_ME_SOME_DYNA
    d->init(100);
    double val;

    d->put(1.0);
    d->put(2.0);
    d->put(3.0);
    d->print_all();
    val = d->get_idx(1);
    dbg("val: %f", val);
    val = d->del_idx(2);
    dbg("deleted: %f", val);
    d->put(199);

    d->destroy();
    return 0;
}

int main1(void)
{
    DynA *d = GIVE_ME_SOME_DYNA
    d->init(10);
    int val;

    d->put(1);
    d->put(2);
    d->put(3);
    d->print_all();
    val = d->get_idx(1);
    dbg("val: %d", val);
    val = d->del_idx(2);
    dbg("deleted: %d", val);
    d->put(199);

    d->destroy();
    return 0;
}
