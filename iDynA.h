#include <stdio.h>
#include <stdlib.h>


#define init        iinit
#define put         iput
#define geti        iget_idx
#define deli        idel_idx
#define print_all   iprint_all
#define deinit      ideinit


#define dbg(fmt, args...) \
    printf("[%s: %d]: (%s) ", __FILE__, __LINE__, __FUNCTION__);\
    printf(fmt, ##args);\
    printf("\n");

typedef struct {
    int *items; // TODO, int...
    int count;
    int capacity;
} DynA;
#define DEFAULT_CAPACITY    (2)

DynA *iinit(int capacity)
{
    DynA *d = malloc(sizeof(DynA));
    if (!d) {
        dbg("%s", "ERROR: malloc failed");
        exit(1);
    }
    if (capacity < DEFAULT_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    d->capacity = DEFAULT_CAPACITY;
    d->count = 0;
    d->items = NULL;
    d->items = malloc(d->capacity*sizeof(*d->items));
    if (!d->items) {
        dbg("%s", "ERROR: malloc failed");
        free(d);
        exit(1);
    }
    return d;
}

DynA *iput(DynA *d, int val)
{
    if (!d) {
        dbg("%s", "ERROR: could not insert");
        return NULL;
    }
    if (d->count >= d->capacity) {
        d->capacity *= 2;
        int *d_items = d->items;
        d->items = malloc(d->capacity*sizeof(*d->items));
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
    return d;
}

int iget_idx(DynA *d, int idx)
{
    if (!d      ||
        idx < 0 ||
        idx > d->count) {
        dbg("%s", "ERROR: could not get the value from index");
        return -1;
    }
    return d->items[idx];
}

int idel_idx(DynA *d, int idx)
{
    if (!d      ||
        idx < 0 ||
        idx > d->count) {
        dbg("%s", "ERROR: could not get the value from index");
        return -1;
    }
    int item = d->items[idx];
    d->items[idx] = -1;
    for (int i = idx; i < d->count; ++i) {
        d->items[i] = d->items[i + 1];
    }
    d->count--;
    return item;
}

DynA *iprint_all(DynA *d)
{
    if (!d) {
        dbg("%s", "ERROR: could not print");
        return NULL;
    }
    for (int i = 0; i < d->count; ++i) {
        printf("%d ", d->items[i]);
    }
    printf("\n");
    return d;
}


int ideinit(DynA *d)
{
    if (!d) {
        dbg("%s", "ERROR: could not autokill");
        return 0;
    }
    free(d->items);
    free(d);
    d=NULL;
    return 1;
}
