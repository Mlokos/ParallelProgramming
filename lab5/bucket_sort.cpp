#include <iostream> // cout
#include <cstdlib>  // rand
#include <omp.h>

#define LL_UINT long long unsigned int
#define UINT unsigned int


// OPENMP
// openmp tutorial (got some example code): https://hpc.llnl.gov/openmp-tutorial
// how to use scheduling: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
// htus part 2, code: https://github.com/jakaspeh/concurrency/blob/master/ompForSchedule.cpp

// BUCKET SORT
// bucket sort algorithm: https://www.geeksforgeeks.org/bucket-sort-2/


// below is a naive implementation; it works but is not in scope of the exercise
// with openmp scheduling usage a 'fill_table' function will not be necessary
void fill_table(int * table, LL_UINT table_size, UINT total_threads, UINT thread_id) {
    LL_UINT elements_chunk = table_size / total_threads;
    // add additional elements to the last thread if there were some inequalities
    if(thread_id == total_threads - 1) {
        UINT additional_elements = table_size % total_threads;
        elements_chunk += additional_elements;
    }
    // iterate through elements
    LL_UINT starting_element = (table_size / total_threads) * thread_id;
    for(LL_UINT i = starting_element; i < starting_element + elements_chunk; ++i) {
        table[i] = std::rand();
    }
}

int main(int argc, char *argv[]) {
    int nthreads, tid;

    int a[103];
    for(int i = 0; i < 103; ++i) {
        a[i] = 0;
    }

    #pragma omp parallel private(tid)
    {
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();

        fill_table(a, 103, nthreads, tid);
    }

    // test
    for(int i = 0; i < 103; ++i) {
        std::cout << a[i] << std::endl;
    }
 }