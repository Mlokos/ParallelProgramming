/**
 * AUTHORS:
 * Ola Pasternak
 * Michal Sokol
 */

#include <iostream> // cout
#include <random>   // uniform_real_distribution
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

    std::vector<float> to_fill_vector(vector_size);
    std::mt19937 gen;
    std::uniform_real_distribution<float> prob(0.0, 1.0);

    auto start_time = std::chrono::high_resolution_clock::now();
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    #pragma omp parallel for shared(to_fill_vector) schedule(runtime)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = prob(gen);
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << duration.count() << std::endl;

    return 0;
 }