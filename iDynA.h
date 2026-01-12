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
    #type,\
    NULL,\
    0,\
    0,\
    type##_init,\
    type##_put,\
    type##_get_idx, \
    type##_del_idx, \
    type##_print_all, \
    type##_destroy,\
}

#ifdef DYNA_INT

struct DynA *int_init(int cap);
struct DynA *int_put(int val);
int         int_get_idx(struct DynA *d, int idx);
int         int_del_idx(struct DynA *d, int idx);
struct DynA *int_print_all(struct DynA *d);
int         int_destroy(struct DynA *d);

struct DynA {
    const char *type_name;

    int *items; // TODO
    int count;
    int capacity;

    struct DynA *(*init)(int cap);
    struct DynA *(*put)(int val);
    int         (*get_idx)(struct DynA *d, int idx);
    int         (*del_idx)(struct DynA *d, int idx);
    struct DynA *(*print_all)(struct DynA *d);
    int         (*destroy)(struct DynA *d);
} DynAs[] = {
    init_with_type(int),
};
typedef struct DynA DynA;


DynA *int_init(int capacity)
{
    DynA *d = &DynAs[0];
TRACINGGG
    if (capacity < DEFAULT_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    d->capacity = DEFAULT_CAPACITY;
    d->count = 0;
    d->items = malloc(d->capacity*sizeof(int));

    if (!d->items) {
        dbg("%s", "ERROR: malloc failed");
        free(d);
        exit(1);
    }

    return d;
}

DynA *int_put(int val)
{
    DynA *d = &DynAs[0];
TRACINGGG
    if (!d) {
        dbg("%s", "ERROR: could not insert");
        return NULL;
    }

    if (d->count >= d->capacity) {
        d->capacity *= 2;
        int *d_items = d->items;
        d->items = malloc(d->capacity*sizeof(int));
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

int int_get_idx(DynA *d, int idx)
{
TRACINGGG
    if (!d      ||
        idx < 0 ||
        idx > d->count) {
        dbg("%s", "ERROR: could not get the value from index");
        return -1;
    }
    return d->items[idx];
}

int int_del_idx(DynA *d, int idx)
{
TRACINGGG
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

DynA *int_print_all(DynA *d)
{
TRACINGGG
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

int int_destroy(DynA *d)
{
TRACINGGG
    if (!d) {
        dbg("%s", "ERROR: could not autokill");
        return 0;
    }
    free(d->items);
    free(d);
    d = NULL;
    return 1;
}
#endif // DYNA_INT

