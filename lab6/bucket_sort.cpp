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
// Function to sort arr[] of
// size n using bucket sort
std::vector<float> bucketSort_0(std::vector<float> arr, int n)
{    
    // 1) Create n empty buckets
    std::vector<float> b[n];

    // 2) Put array elements
    // in different buckets
    auto bucket_split_start = std::chrono::high_resolution_clock::now();
    for (LLONG_UINT i = 0; i < arr.size(); i++) {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }
    auto bucket_split_end = std::chrono::high_resolution_clock::now();
 
    // 3) Sort individual buckets
    auto bucket_sort_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        std::sort(b[i].begin(), b[i].end());
    auto bucket_sort_end = std::chrono::high_resolution_clock::now();
 
    // 4) Concatenate all buckets into arr[]
    auto bucket_to_array_start = std::chrono::high_resolution_clock::now();
    LLONG_UINT index = 0;
    for (int i = 0; i < n; i++)
        for (LLONG_UINT j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
    
    auto bucket_to_array_end = std::chrono::high_resolution_clock::now();

    auto bucket_split_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_split_end - bucket_split_start);
    auto bucket_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_sort_end - bucket_sort_start);
    auto bucket_to_array_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_to_array_end - bucket_to_array_start);
    
    std::cout << "bucket_split_time " << bucket_split_duration.count() << std::endl;
    std::cout << "bucket_sort_time " << bucket_sort_duration.count() << std::endl;
    std::cout << "bucket_to_array_time " << bucket_to_array_duration.count() << std::endl;

    return arr;
}


// source: https://www.geeksforgeeks.org/bucket-sort-2/
// author: Michal Sokol
// Function to sort arr[] of
// size n using bucket sort
std::vector<float> bucketSort_2(std::vector<float> arr, int n)
{
    // 1) Create n empty buckets
    std::vector<float> b[n];
 
    // 2) Put array elements
    // in different buckets
    auto bucket_split_start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for schedule(runtime)
    for (LLONG_UINT i = 0; i < arr.size(); ++i) {
        int bi = n * arr[i]; // Index in bucket
        #pragma omp critical
        b[bi].push_back(arr[i]);
    }
    auto bucket_split_end = std::chrono::high_resolution_clock::now();
 
    // 3) Sort individual buckets
    auto bucket_sort_start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        std::sort(b[omp_get_thread_num()].begin(), b[omp_get_thread_num()].end());
    }
    auto bucket_sort_end = std::chrono::high_resolution_clock::now();

    // 4) Concatenate all buckets into arr[]
    auto bucket_to_array_start = std::chrono::high_resolution_clock::now();
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
    auto bucket_to_array_end = std::chrono::high_resolution_clock::now();

    auto bucket_split_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_split_end - bucket_split_start);
    auto bucket_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_sort_end - bucket_sort_start);
    auto bucket_to_array_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_to_array_end - bucket_to_array_start);
    
    std::cout << "bucket_split_time " << bucket_split_duration.count() << std::endl;
    std::cout << "bucket_sort_time " << bucket_sort_duration.count() << std::endl;
    std::cout << "bucket_to_array_time " << bucket_to_array_duration.count() << std::endl;

    return arr;
}


int main(int argc, char *argv[]) {
    /**
    * Arguments handle
    */
    if(argc != 3) {
        printf("Run program with a points quantity argument and algorithm type!\n");
        exit(1);
    }
    char *ptr;
    LLONG_UINT vector_size = strtol(argv[1], &ptr, 10);
    int algorithm_type = atoi(argv[2]);

    std::vector<float> to_fill_vector(vector_size);
    std::mt19937 gen;
    std::uniform_real_distribution<float> prob(0.0, 1.0);

    // Indicate start of the program iteration
    std::cout << "-------" << std::endl;

    auto program_start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for shared(to_fill_vector) schedule(runtime)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = prob(gen);
    }
    auto fill_table_end_time = std::chrono::high_resolution_clock::now();

    int available_threads;
    #pragma omp parallel
    {
        if(omp_get_thread_num() == 0)
            available_threads = omp_get_num_threads();
    }

    switch(algorithm_type) {
        case 0:
            to_fill_vector = bucketSort_0(to_fill_vector, available_threads);
            break;
        case 2:
            to_fill_vector = bucketSort_2(to_fill_vector, available_threads);
            break;
        default:
            std::cout << "No such algorithm!\n";
    }
    auto program_end_time = std::chrono::high_resolution_clock::now();

    auto fill_table_duration = std::chrono::duration_cast<std::chrono::microseconds>(fill_table_end_time - program_start_time);
    auto program_duration = std::chrono::duration_cast<std::chrono::microseconds>(program_end_time - program_start_time);

    std::cout << "table_fill_time " << fill_table_duration.count() << std::endl;
    std::cout << "program_time " << program_duration.count() << std::endl;

    return 0;
 }