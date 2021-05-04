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


void generate_table(std::vector<float> to_fill_vector, std::mt19937 gen, std::uniform_real_distribution<float> prob) {
    #pragma omp parallel for shared(to_fill_vector) schedule(static, 8)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = prob(gen);
    }
}


// source: https://www.geeksforgeeks.org/bucket-sort-2/
// Function to sort arr[] of
// size n using bucket sort
std::vector<float> bucketSort(std::vector<float> arr, int n)
{
    // 1) Create n empty buckets
    std::vector<float> b[n];
 
    // 2) Put array elements
    // in different buckets
    #pragma omp parallel for schedule(static, 8)
    for (LLONG_UINT i = 0; i < arr.size(); ++i) {
        int bi = n * arr[i]; // Index in bucket
        #pragma omp critical
        b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets
    #pragma omp parallel for schedule(static, 8)
    for (int i = 0; i < n; i++)
        std::sort(b[i].begin(), b[i].end());
 
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    #pragma omp parallel for schedule(static, 8)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];

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

    // generate_table(to_fill_vector, gen, prob);
    #pragma omp parallel for shared(to_fill_vector) schedule(static, 8)
    for(LLONG_UINT i=0; i < to_fill_vector.size(); ++i) {
        to_fill_vector[i] = prob(gen);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    to_fill_vector = bucketSort(to_fill_vector, 4);
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << duration.count() << std::endl;

    return 0;
 }