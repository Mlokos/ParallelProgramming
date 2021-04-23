#include <iostream> // cout
#include <cstdlib>  // rand
#include <omp.h>

// OPENMP
// openmp tutorial (got some example code): https://hpc.llnl.gov/openmp-tutorial
// how to use scheduling: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
// htus part 2, code: https://github.com/jakaspeh/concurrency/blob/master/ompForSchedule.cpp
// htus part 3: those links provided in laboratory are actually pretty fine
// openmp sheduling for 'runtime' type, code: https://www.rookiehpc.com/openmp/docs/omp_set_schedule.php

// BUCKET SORT
// bucket sort algorithm: https://www.geeksforgeeks.org/bucket-sort-2/


#define TABLE_SIZE 1024

int main(int argc, char *argv[]) {
    int to_fill_table[TABLE_SIZE];
    // omp_set_schedule(omp_sched_dynamic, 2); // use only with 'runtime' schedule

    // different types of sheduling
    #pragma omp parallel for shared(to_fill_table) schedule(static, 1)
    // #pragma omp parallel for shared(to_fill_table) schedule(dynamic, 1)
    // #pragma omp parallel for shared(to_fill_table) schedule(guided, 1)
    // #pragma omp parallel for shared(to_fill_table) schedule(auto) // this one is without a second parameter; compiler is taking care of this and takes the best one
    // #pragma omp parallel for shared(to_fill_table) schedule(runtime) // this one is also without a second parameter; 
    for(int i = 0; i < TABLE_SIZE; ++i) {
        to_fill_table[i] = rand();
    }

    // test
    for(int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << to_fill_table[i] << std::endl;
    }
 }