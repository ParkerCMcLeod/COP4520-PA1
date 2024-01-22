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


void segmentedSieve(unsigned int l, unsigned int r, std::vector<bool>& prime_array, unsigned int& total_primes, unsigned long long& sum_of_primes) {

    int sqrt_r = sqrt(r);

    // regular sieve of eratosthenes to find primes up to sqrt(r)
    prime_array[0] = prime_array[1] = false;
    for (unsigned long long i = 2; i*i <= sqrt_r; i++) {
        if (prime_array[i]) {
            for (unsigned long long j = i*i; j <= sqrt_r; j += i)
                prime_array[j] = false;

            // apply the sieve to [l,r]
            unsigned long long start = std::max(i * i, (l + i - 1) / i * i);
            for (unsigned long long k = start; k <= r; k += i) {
                prime_array[k - l] = false;
            }
        }
    }

    // collect primes in the segmented range
    for (unsigned long long i = 0; i <= r - l; i++) {
        if (prime_array[i]) {
            total_primes++;
            sum_of_primes += i + l;
        }
    }
}

void get_ten_largest_primes_ascending(unsigned int n, std::vector<bool>& prime_array, std::vector<unsigned int>& ten_largest_primes_ascending) {
    // get the ten largest primes by traveling from top to bottom
    for (unsigned long long i = n-1; i >= 2 && ten_largest_primes_ascending.size() < 10; i--) {
        if (prime_array[i])
            ten_largest_primes_ascending.push_back(i);
    }
}

void save_to_file(std::chrono::milliseconds execution_time, int total_primes, long long sum_of_primes, const std::vector<unsigned int>& ten_largest_primes_ascending) {
    std::ofstream outFile("primes.txt");
    if (outFile.is_open()) {
        outFile << execution_time.count() << " " << total_primes << " " << sum_of_primes << std::endl;

    // we recorded the ten in descending order, so print backwards
    for (int i = ten_largest_primes_ascending.size() - 1; i >= 0; i--) {
        outFile << ten_largest_primes_ascending[i] << " ";
    }
        
    outFile << std::endl;
    outFile.close();
    } else {
        std::cerr << "Error opening primes.txt." << std::endl;
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect number of parameters passed. Usage is prime_finder [n]." << std::endl;
        return 1; // exit
    }

    unsigned long long n = std::stoull(argv[1]);
    if (n < 2) {
        std::cerr << "No primes less than 2." << std::endl;
        return 1;
    }

    // timer start
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<bool> prime_array(n, true);

    std::vector<unsigned int> ten_largest_primes_ascending;
    ten_largest_primes_ascending.reserve(10);

    unsigned long long sum_of_primes = 0;
    unsigned int total_primes = 0;

    segmentedSieve(2, n, prime_array, total_primes, sum_of_primes);

    get_ten_largest_primes_ascending(n, prime_array, ten_largest_primes_ascending);

    // timer end
    auto stop = std::chrono::high_resolution_clock::now();

    // timer calc
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // save vars, formatted to spec
    save_to_file(execution_time, total_primes, sum_of_primes, ten_largest_primes_ascending);

    return 0;
}