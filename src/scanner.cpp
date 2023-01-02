#include "includes.h"
#include "functions.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("\nUsage: fastscan [THREADS] [PORT] [TIMEOUT]\n\n");
        exit(1);
    }

    int threadCount = atoi(argv[1]);

    std::thread workers[threadCount];

    for (int i = 0; i < threadCount; i++)
    {
        workers[i] = std::thread(worker_thread, threadCount, i, atoi(argv[2]), atoi(argv[3]));
        workers[i].detach();
    }

    while (1)
        ;
}
