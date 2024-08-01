#include "common.h"

enum
{
    VAL_MIN,
    VAL_MAX,
    VAL_MEAN
};

typedef struct
{
    char name[64];
    u32 id;
    double val[3];
    u32 count; /**< Number of mean values */
} MapItem;

typedef struct
{
    MapItem item[100000];
    u32 count; /**< Number of items */
} Map;

static Map map = {
    .count = 0
};

static inline u32 read_lines(char *buff, FILE *fh, u32 count)
{
    char *start = buff;

    u32 lines_read = 0;
    s32 c;
    while ((c = getc(fh)) != EOF)
    {
        *buff++ = (char)c;
        if (c == '\n')
            lines_read++;
        if (count == lines_read)
            break;
    }
    *buff = '\0';

    return buff - start;
}

static inline void map_add(char *name, u32 id, double val)
{
    for (u32 i = 0; i < map.count; i++)
    {
        MapItem *item = &map.item[i];
        if (item->id == id)
        {
            item->val[VAL_MIN] = MIN(item->val[VAL_MIN], val);
            item->val[VAL_MAX] = MAX(item->val[VAL_MAX], val);
            item->val[VAL_MEAN] += (val - item->val[VAL_MEAN]) / ++(item->count);
            return;
        }
    }

    MapItem *item = &map.item[map.count++];

    u32 name_size = sizeof(item->name);

    strncpy(item->name, name, name_size - 1);
    item->name[name_size - 1] = '\0';
    item->id = id;
    item->val[VAL_MIN] = DBL_MAX;
    item->val[VAL_MAX] = -DBL_MAX;
    item->val[VAL_MEAN] = 0;
    item->count = 0;
}

static s32 qsort_callback(const void *a, const void *b)
{
    MapItem *x = (MapItem *)a;
    MapItem *y = (MapItem *)b;
    return strncmp(x->name, y->name, sizeof(x->name));
}

static inline u32 hash_djb2(char *key)
{
    u32 hash = 0x1505;
    while (*key)
        hash = ((hash << 0x5) + hash) + *key++;
    return hash;
}

void run_solution_1(char *path)
{
    char buff[1000 * 1000] = {0};

    FILE *fh = fopen(path, "r");

    while (read_lines(buff, fh, 500))
    {
        char *ptr = buff;

        while (*ptr)
        {
            char *sep = strchr(ptr, ',');
            *sep = '\0';
            char *name = &*ptr;
            ptr += (sep - ptr) + 1;

            u32 hash = hash_djb2(name);

            sep = strchr(ptr, '\n');
            *sep = '\0';
            double value = atof(ptr);
            ptr += (sep - ptr) + 1;

            map_add(name, hash, value);
        }
    }

    qsort(map.item, map.count, sizeof(MapItem), qsort_callback);

    for (u32 i = 0; i < map.count; i++)
    {
        MapItem *item = &map.item[i];
        printf("%s %.01f,%.01f,%.01f\n", item->name, item->val[VAL_MIN], item->val[VAL_MAX], item->val[VAL_MEAN]);
    }

    fclose(fh);
}
