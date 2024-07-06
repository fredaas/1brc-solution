#include "common.h"

char *names[] = {"Praia", "Pretoria", "Pyongyang", "Rabat", "Rangpur", "Reggane", "Reykjavík", "Riga",
         "Riyadh", "Rome", "Roseau", "Rostov-on-Don", "Sacramento", "Saint Petersburg", "Saint-Pierre",
         "Salt Lake City", "San Antonio", "San Diego", "San Francisco", "San Jose", "San José",
         "San Juan", "San Salvador", "Sana'a", "Santo Domingo", "Sapporo", "Sarajevo", "Saskatoon",
         "Seattle", "Ségou", "Seoul", "Seville", "Shanghai", "Singapore", "Skopje", "Sochi", "Sofia"};

#define rand_float(a, b) ((f64)(a) + ((b) - (a)) * (rand() / (f64)RAND_MAX))

void write_data(u32 count)
{
    FILE *fh = fopen(MEASUREMENTS_PATH, "w");
    u32 num_names = sizeof(names) / sizeof(names[0]);
    for (u32 i = 0; i < count; i++)
        fprintf(fh, "%s,%.01lf\n", names[rand() % num_names], rand_float(-100, 100));
    fclose(fh);
}

int main(int argc, char const *argv[])
{
    srand(0xDEADBEEF);

    argc--;

    if (argc == 0)
    {
        printf(
            "Usage:\n"
            "    gendata <rows>\n"
            "\n"
            "Options:\n"
            "    rows\n"
            "        Number of rows to generate.\n");
        return 1;
    }

    u32 count = strtol(argv[1], NULL, 10);

    write_data(count);

    return 0;
}