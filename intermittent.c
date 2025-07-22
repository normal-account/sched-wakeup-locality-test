#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#define BENCH_RUN_TIME_S  30    // total bench run time (in seconds)
#define BURST_INTERVAL_MS 2     // interval which separates our busy loops (in ms)
#define BURST_DURATION_MS 3     // how long the CPU bursts last (in ms)
#define NUM_THREADS 1           // increase for higher CPU %

volatile bool run_burst = false;
volatile unsigned long long x = 0;

double now_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        printf("Usage : ./run_intermittent_burn <client id>\n");
        return 1;
    }

    double start = now_seconds();
    double last_sample = start;
    double last_burst = start;
    double now = 0;
    double elapsed = 0;

    while (elapsed < 30) {
        now = now_seconds();
        elapsed = now - start;

        double iteration = 0;
        while (iteration < BURST_DURATION_MS) {
            for (unsigned long i = 0; i < 1e9; i++) {
                if ( ( i % 1000 ) == 0 )
                {
                    x += 1; // increment every 1000 iterations
                }
                if ( ( i % 100 ) == 0 )
                {
                    iteration = ( now_seconds() - now ) * 1000.0;
                    if ( iteration >= BURST_DURATION_MS ) break;
                }
            }
        }

        usleep(BURST_INTERVAL_MS * 1000);  // run burst for short time
    }

    int client_num = atoi( argv[1] );

    usleep( 10000 * client_num-1 ); // so that our clients print in order

    if ( client_num == 1 ) printf("\n");

    printf("Iterations for worker %s : %lldm\n", argv[1], x/1000);

    return 0;
}
