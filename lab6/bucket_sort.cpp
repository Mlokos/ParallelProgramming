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

std::vector<std::vector<std::vector<float>>> createBucketsForThread(int n) {
    std::vector<float> bucket;
    std::vector<std::vector<float>> buckets(n, bucket);
    std::vector<std::vector<std::vector<float>>> thread_buckets(4, buckets);
    return thread_buckets;
}

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
    
    std::cout << "bucket_split_time " << (double)bucket_split_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_sort_time " << (double)bucket_sort_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_to_array_time " << (double)bucket_to_array_duration.count()/1000000 << " [s]"  << std::endl;

    return arr;
}

std::vector<float> bucketSort_1(std::vector<float> arr, int numberOfThreads, int n) {
    // Create n empty buckets for every thread
    std::vector<std::vector<std::vector<float>>> thread_buckets = createBucketsForThread(numberOfThreads);

    // range for one bucket
    float interval = float(1) / (numberOfThreads * n);

    // Fill the buckets 
    auto bucket_split_start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel 
    {
        int threadId = omp_get_thread_num();
        float minValue = (float(1) * threadId) / numberOfThreads;
        // set starting point different for every thread
        LLONG_UINT startIndex = arr.size() / (threadId + 1);
        float number;

        for (LLONG_UINT i=0; i<arr.size(); i++) {
            number = arr[(i+startIndex)%arr.size()];
            for (int j=0; j<n; j++) {
                if (number >= (minValue + j*interval) && number < (minValue + (j+1)*interval)) {
                    thread_buckets[threadId][j].push_back(number);
                    break;
                }
            }
        }
    }
    auto bucket_split_end = std::chrono::high_resolution_clock::now();

    // Sort individual buckets
    auto bucket_sort_start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel 
    {
        int threadId = omp_get_thread_num();
        for (int j=0; j<n; j++) {
            std::sort(thread_buckets[threadId][j].begin(), thread_buckets[threadId][j].end());
        }
    }
    auto bucket_sort_end = std::chrono::high_resolution_clock::now();

    // Before writing to input array wait until all threads read an array and filled buckets
    #pragma omp barrier

    auto bucket_to_array_start = std::chrono::high_resolution_clock::now();
    // Get start indexes in input array for threads
    LLONG_UINT bucket_size;
    std::vector<LLONG_UINT> arr_indexes (numberOfThreads);
    for(int i = 0; i < numberOfThreads; i++) arr_indexes[i] = 0;

    for(int i = 0; i < numberOfThreads; i++) {
        for(int j = 0; j < n; j++) {
            bucket_size = thread_buckets[i][j].size();
            for(int k = i + 1; k < numberOfThreads; k++) {
                arr_indexes[k] += bucket_size;
            }
        }
    }

    // Write buckets into input array
    LLONG_UINT startIndex;
    #pragma omp parallel private(startIndex)
    {
        int threadId = omp_get_thread_num();
        startIndex = (threadId == 0) ? 0 : arr_indexes[threadId];

        for(int j = 0; j < n; j++) {
            for(std::vector<float>::iterator it = thread_buckets[threadId][j].begin(); it != thread_buckets[threadId][j].end(); ++it) {
                arr[startIndex] = *it;
                startIndex++;
            }
        }
    }

    auto bucket_to_array_end = std::chrono::high_resolution_clock::now();

    auto bucket_split_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_split_end - bucket_split_start);
    auto bucket_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_sort_end - bucket_sort_start);
    auto bucket_to_array_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_to_array_end - bucket_to_array_start);
    
    std::cout << "bucket_split_time " << (double)bucket_split_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_sort_time " << (double)bucket_sort_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_to_array_time " << (double)bucket_to_array_duration.count()/1000000 << " [s]"  << std::endl;

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
        int thread_number = omp_get_thread_num();
        for (LLONG_UINT table_it = bucket_sizes[thread_number]; table_it < bucket_sizes[thread_number + 1]; ++table_it) {
            arr[table_it] = b[thread_number][table_it - bucket_sizes[thread_number]];
        }
    }
    auto bucket_to_array_end = std::chrono::high_resolution_clock::now();

    auto bucket_split_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_split_end - bucket_split_start);
    auto bucket_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_sort_end - bucket_sort_start);
    auto bucket_to_array_duration = std::chrono::duration_cast<std::chrono::microseconds>(bucket_to_array_end - bucket_to_array_start);
    
    std::cout << "bucket_split_time " << (double)bucket_split_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_sort_time " << (double)bucket_sort_duration.count()/1000000 << " [s]"  << std::endl;
    std::cout << "bucket_to_array_time " << (double)bucket_to_array_duration.count()/1000000 << " [s]"  << std::endl;

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
        case 1:
            to_fill_vector = bucketSort_1(to_fill_vector, available_threads, 4);
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

    std::cout << "table_fill_time " << (double)fill_table_duration.count()/1000000 << " [s]" << std::endl;
    std::cout << "program_time " << (double)program_duration.count()/1000000 << " [s]" << std::endl;

    return 0;
 }