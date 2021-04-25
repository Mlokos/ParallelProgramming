/**
 * AUTHORS:
 * Ola Pasternak
 * Michal Sokol
 */

#include <iostream> // cout
#include <cstdlib>  // rand
#include <vector>   // vector
#include <chrono>   // time
#include <omp.h>

#define LLONG_UINT unsigned long long int


int main(int argc, char *argv[]) {
    /**
    * Arguments handle
    */
    if(argc != 2) {
        printf("Run program with a points quantity argument!");
        exit(1);
    }
    char *ptr;
    LLONG_UINT vector_size = strtol(argv[1], &ptr, 10);

    std::vector<int> to_fill_vector(vector_size);

    auto start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for shared(to_fill_vector) schedule(runtime)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = rand();
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << duration.count() << std::endl;

    return 0;
 }