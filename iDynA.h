#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY    (10)
#define TRACINGGG   dbg("%s", "<- O_o");
// #define TRACINGGG   /*nothing*/

#define dbg(fmt, args...) \
    printf("[%s: %d]: (%s) ", __FILE__, __LINE__, __FUNCTION__);\
    printf(fmt, ##args);\
    printf("\n");

#define init_with_type(type) {\
    NULL,\
    0,\
    0,\
    init,\
    put,\
    get_idx, \
    del_idx, \
    print_all, \
    destroy,\
}

#ifndef TYPE
#define TYPE int
#endif

void init(int cap);
void put (TYPE val);
TYPE        get_idx(int idx);
TYPE        del_idx(int idx);
void        print_all(void);
void        destroy(void);

struct DynA {
    int *items;
    int count;
    int capacity;

    void (*init)(int cap);
    void (*put) (TYPE val);
    TYPE        (*get_idx)(int idx);
    TYPE        (*del_idx)(int idx);
    void        (*print_all)(void);
    void        (*destroy)(void);
} dynas[] = {
    init_with_type(TYPE), //TODO
};
typedef struct DynA DynA;
#define GIVE_ME_SOME_DYNA    &dynas[0];

void init(int capacity)
{
    DynA *d = GIVE_ME_SOME_DYNA
TRACINGGG
    if (capacity < DEFAULT_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    d->capacity = DEFAULT_CAPACITY;
    d->count = 0;
    d->items = malloc(d->capacity*sizeof(TYPE));

    if (!d->items) {
        dbg("%s", "ERROR: malloc failed");
        free(d);
        exit(1);
    }
}

void put(TYPE val)
{
TRACINGGG
    DynA *d = GIVE_ME_SOME_DYNA
    if (!d) {
        dbg("%s", "ERROR: could not insert");
        exit(1);
    }

    if (d->count >= d->capacity) {
        d->capacity *= 2;
        int *d_items = d->items;
        d->items = malloc(d->capacity*sizeof(TYPE));
        if (!d->items) {
            dbg("%s", "ERROR: could not malloc");
            free(d_items);
            free(d);
            exit(1);
        }
        for (int i = 0; i < d->count; ++i) {
            d->items[i] = d_items[i];
        }
        free(d_items);
    }
    d->items[d->count++] = val;
}

TYPE get_idx(int idx)
{
TRACINGGG
    DynA *d = GIVE_ME_SOME_DYNA
    if (!d      ||
        idx < 0 ||
        idx > d->count) {
        dbg("%s", "ERROR: could not get the value from index");
        return -1;
    }
    return d->items[idx];
}

TYPE del_idx(int idx)
{
TRACINGGG
    DynA *d = GIVE_ME_SOME_DYNA
    if (!d      ||
        idx < 0 ||
        idx > d->count) {
        dbg("%s", "ERROR: could not get the value from index");
        return -1;
    }
    TYPE item = d->items[idx];
    d->items[idx] = -1;
    for (int i = idx; i < d->count; ++i) {
        d->items[i] = d->items[i + 1];
    }
    d->count--;
    return item;
}

void print_all(void)
{
TRACINGGG
    DynA *d = GIVE_ME_SOME_DYNA
    if (!d) {
        dbg("%s", "ERROR: could not print");
        exit(1);
    }
    for (int i = 0; i < d->count; ++i) {
        printf("%d ", d->items[i]); // TODO: fixme
    }
    printf("\n");
}

void destroy(void)
{
TRACINGGG
    DynA *d = GIVE_ME_SOME_DYNA
    if (!d) {
        dbg("%s", "ERROR: could not autokill");
        exit(1);
    }
    free(d->items);
    d = NULL;
}
