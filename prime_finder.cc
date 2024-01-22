/*
COP4520-24Spring 0V01: Concept of Parallel and Distributed Processing
Programming Assignment 1
Instructor: Juan Parra
Due date: Friday, January 26th by 11:59 PM
*/


#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>


void save_to_file(std::chrono::milliseconds execution_time, int total_primes, long long sum_of_primes, std::vector<int>& ten_largest_primes_ascending) {
    std::ofstream outFile("primes.txt");
    if (outFile.is_open()) {
        outFile << execution_time.count() << " " << total_primes << " " << sum_of_primes << std::endl;

        for(int i=0; i<ten_largest_primes_ascending.size(); i++)
            outFile << ten_largest_primes_ascending[i] << " ";

        outFile.close();
    } else {
        std::cerr << "Error opening primes.txt." << std::endl;
    }
}


int main(int argc, char *argv[]) {

    // timer start
    auto start = std::chrono::high_resolution_clock::now();

    if(argc != 2)
        std::cerr << "Incorrect number of parameters passed. Usage is prime_finder [n]." << std::endl;

    unsigned long long n = std::atoi(argv[1]);

    // create a bool array of size n assumed to be primes
    std::vector<bool> A;
    A.reserve(n);

    int total_primes = {};
    
    unsigned long long sum_of_primes = {}; // guranteed to be at least 2^64 - 1 in C++11

    std::vector<int> ten_largest_primes_ascending;
    ten_largest_primes_ascending.reserve(10);

    for(int i=2; i < std::sqrt(n); i++) {
        int j = i * i;
        while(j<=n) {
            A[j] = false;
            j++;
        }
    }

    for(int i=2; i < n; i++)
        if(A[i]) 
            total_primes++;

    // timer end
    auto stop = std::chrono::high_resolution_clock::now();

    // timer calc
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    save_to_file(execution_time, total_primes, sum_of_primes, ten_largest_primes_ascending);

    return 0;
}