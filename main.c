#include "common.h"

f64 walltime(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec * 10e-6;
}

typedef void (*solution_fn_t)(char *path);

void bench(solution_fn_t fn)
{
    f64 start = walltime();
    fn(MEASUREMENTS_PATH);
    printf("%.04lf\n", walltime() - start);
}

int main(int argc, char const *argv[])
{
    bench(run_solution_1);

    return 0;
}
