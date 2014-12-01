#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int repeats = 10;
double float_limit = 10.0;
double float_limit_sub = 9.0;
int int_limit = 10000;
int int_limit_sub = 9000;
const int floats_length = (1024 * 1024);
const int ints_length = (1024 * 1024);
float floats[floats_length];
int ints[ints_length];
clock_t end, start;

int run_test(void)
{
    int i, j, mask;
    float floats_process_time_ms, ints_process_time_ms;
	clock_t clock(void);
    printf("DrAF.SimplePerfTest\n");
    printf("Preparing...\n");

    // »нициализируем генератор случайных чисел
    srand(time(NULL));

    for(i = 0; i < floats_length; ++i)
    {
        floats[i] = ((float)rand() / (float)RAND_MAX) * float_limit + 1.0f;
    }

    for(i = 0; i < ints_length; ++i)
    {
        ints[i] = (int)(((float)rand() / (float)RAND_MAX) * int_limit + 1);
    }

    printf("Multiplying %d floats, %d ints\n", floats_length, ints_length);

    // Start floats test
	start=clock();
    for(i = 0; i < repeats; ++i)
    {
        for(j = 0; j < floats_length; ++j)
        {
            floats[j + 1] = floats[j + 1] * floats[j];
            while(floats[j + 1] > float_limit)
            {
                floats[j + 1] -= float_limit_sub;
            }
        }
    }
	end = clock();
	floats_process_time_ms = (float)((long double)(end - start)*(long double)1000.0 / (long double)CLOCKS_PER_SEC);
    floats_process_time_ms /= repeats;
    printf("Floats result (ms): %5.2f\n", floats_process_time_ms);

    // Start ints test
	start = clock();
    mask = 1023;
    for(i = 0; i < repeats; ++i)
    {
        for(j = 0; j < (ints_length - 1); ++j)
        {
            ints[j + 1] = (ints[j + 1] * ints[j]) % mask + 97;
        }
    }

	end = clock();
	ints_process_time_ms = (float)((long double)(end - start)*(long double)1000.0 / (long double)CLOCKS_PER_SEC);
    ints_process_time_ms /= repeats;
    printf("Ints result (ms): %5.2f\n", ints_process_time_ms);
	getchar();
	return 0;
}

