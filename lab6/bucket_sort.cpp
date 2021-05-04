/**
 * AUTHORS:
 * Ola Pasternak
 * Michal Sokol
 */

#include <iostream> // cout
#include <random>   // uniform_real_distribution
#include <vector>   // vector
#include <chrono>   // time
#include <algorithm>
#include <omp.h>

#define LLONG_UINT unsigned long long int


// source: https://www.geeksforgeeks.org/bucket-sort-2/
// author: Michal Sokol
// Function to sort arr[] of
// size n using bucket sort
std::vector<float> bucketSort(std::vector<float> arr, int n)
{
    // 1) Create n empty buckets
    std::vector<float> b[n];
 
    // 2) Put array elements
    // in different buckets
    #pragma omp parallel for schedule(runtime)
    for (LLONG_UINT i = 0; i < arr.size(); ++i) {
        int bi = n * arr[i]; // Index in bucket
        #pragma omp critical
        b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets
    #pragma omp parallel
    {
        std::sort(b[omp_get_thread_num()].begin(), b[omp_get_thread_num()].end());
    }

    // 4) Concatenate all buckets into arr[]
    std::vector<LLONG_UINT> bucket_sizes;
    for(int i = 0; i < n; ++i) {
        if(i > 0) {
            bucket_sizes.push_back(b[i].size() + bucket_sizes.back());
        } else {
            bucket_sizes.push_back(b[i].size());
        }
    }
    bucket_sizes.insert(bucket_sizes.begin(), 0);
    
    #pragma omp parallel
    {
        for(int thread_number = 0; thread_number < n; ++thread_number){
            if(omp_get_thread_num() == thread_number) {
                for (LLONG_UINT table_it = bucket_sizes[thread_number]; table_it < bucket_sizes[thread_number]; ++table_it) {
                    for (LLONG_UINT bucket_it = 0; bucket_it < b[thread_number].size(); ++bucket_it) {
                        arr[table_it + bucket_it] = b[thread_number][bucket_it];
                    }
                }
            }
        }
    }

    return arr;
}


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

    #pragma omp parallel for shared(to_fill_vector) schedule(runtime)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = prob(gen);
    }

    int available_threads;
    #pragma omp parallel
    {
        if(omp_get_thread_num() == 0)
            available_threads = omp_get_num_threads();
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    to_fill_vector = bucketSort(to_fill_vector, available_threads);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << duration.count() << std::endl;

    return 0;
 }