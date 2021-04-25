#include <iostream> // cout
#include <cstdlib>  // rand
#include <vector>   // vector
#include <omp.h>

#define TABLE_SIZE 1024

// OPENMP
// openmp tutorial (got some example code): https://hpc.llnl.gov/openmp-tutorial
// how to use scheduling: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
// htus part 2, code: https://github.com/jakaspeh/concurrency/blob/master/ompForSchedule.cpp
// htus part 3: those links provided in laboratory are actually pretty fine
// openmp sheduling for 'runtime' type, code: https://www.rookiehpc.com/openmp/docs/omp_set_schedule.php

// BUCKET SORT
// bucket sort algorithm: https://www.geeksforgeeks.org/bucket-sort-2/

void fill_table_static(std::vector<int> &table, int chunk_size) {
    #pragma omp parallel for shared(table) schedule(static, chunk_size)
    for(auto &elem: table) {
        elem = rand();
    }
}

void fill_table_dynamic(std::vector<int> &table, int chunk_size) {
    #pragma omp parallel for shared(table) schedule(dynamic, chunk_size)
    for(auto &elem: table) {
        elem = rand();
    }
}

void fill_table_guided(std::vector<int> &table, int chunk_size) {
    #pragma omp parallel for shared(table) schedule(guided, chunk_size)
    for(auto &elem: table) {
        elem = rand();
    }
}

void fill_table_auto(std::vector<int> &table) {
    #pragma omp parallel for shared(table) schedule(auto)
    for(auto &elem: table) {
        elem = rand();
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> to_fill_vector(TABLE_SIZE);

    fill_table_static(to_fill_vector, 1);

    // test
    std::cout << to_fill_vector.size() << std::endl;
    for(auto &elem: to_fill_vector) {
        std::cout << elem << std::endl;
    }
 }