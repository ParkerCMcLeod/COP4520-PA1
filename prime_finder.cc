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
#include <thread>
#include <vector>


#define NUM_THREADS 8


struct prime_struct {
    int start;
    int end;
    std::vector<bool> is_prime_array;
    unsigned long long sum_of_primes;
    unsigned int total_primes;
};

void create_sieve_sections(std::vector<prime_struct>& prime_struct_array, int n) {

    int num_sections = prime_struct_array.size();

    // calculate section sizes 
    int sectionSize = n / num_sections;
    int extra = n % num_sections;
    
    // indicies
    int start = 0, end = 0;

    for (int i = 0; i < num_sections; ++i) {
        start = end; // pickup where the last section left off
        prime_struct_array[i].start = start;
        
        end += sectionSize + (i < extra); // extra element for first 'extra' sections
        prime_struct_array[i].end = end;

        // create/store sections
        prime_struct_array[i].is_prime_array = std::vector<bool>(end-start, true);
    }

}

// implementation via https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve
void segmented_sieve(prime_struct& prime) {

    unsigned long long r = prime.end;
    unsigned long long sqrt_r = sqrt(r);
    std::vector<bool> is_prime_sqrt_r(sqrt_r + 1, true);

    // 0 and 1 are not prime
    if(prime.start == 0)
        prime.is_prime_array[0] = prime.is_prime_array[1] = false;

    // regular sieve of eratosthenes to find primes up to sqrt(r)
    for (unsigned long long i = 2; i * i <= sqrt_r; ++i) {
        if (is_prime_sqrt_r[i]) {
            for (unsigned long long j = i * i; j <= sqrt_r; j += i)
                is_prime_sqrt_r[j] = false;
        }
    }

    // apply the sieve to [l,r]
    for (unsigned long long i = 2; i <= sqrt_r; ++i) {
        if (is_prime_sqrt_r[i]) {
            unsigned long long start = std::max(i * i, (prime.start + i - 1) / i * i);
            for (unsigned long long k = start; k < prime.end; k += i) {
                prime.is_prime_array[k - prime.start] = false;
            }
        }
    }

    for (unsigned long long i = 0; i < prime.is_prime_array.size(); ++i) {
        if (prime.is_prime_array[i]) {
            prime.total_primes++;
            prime.sum_of_primes += i + prime.start;
        }
    }

}

// get ten largest primes from prime array
void get_ten_largest_primes_ascending(unsigned int n, std::vector<bool>& prime_array, std::vector<unsigned int>& ten_largest_primes_ascending) {
    // get the ten largest primes by traveling from top to bottom
    for (unsigned long long i = n-1; i >= 2 && ten_largest_primes_ascending.size() < 10; i--) {
        if (prime_array[i])
            ten_largest_primes_ascending.push_back(i);
    }
}

// save to the file in specified format
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

    auto start = std::chrono::high_resolution_clock::now();

    int num_threads = std::thread::hardware_concurrency(); // dynamic max thread selection
    
    if (num_threads == 0) {
        std::cout << "Unable to determine the number of CPU threads." << std::endl;
        return 1;
    }

    num_threads = NUM_THREADS; // adjusted for PA1 requirements
    
    std::vector<prime_struct> prime_struct_array(num_threads);

    // populate bool arrays and indicies within sections
    create_sieve_sections(prime_struct_array, n);

    std::vector<std::thread> threads;

    // create and start the threads
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(segmented_sieve, std::ref(prime_struct_array[i])));
    }

    // wait for threads to complete
    for (std::thread &th : threads) {
        th.join();
    }

    std::vector<bool> joined_prime_arrays;
    joined_prime_arrays.reserve(n);
    unsigned int joined_total_primes = 0;
    unsigned long long joined_sum_of_primes = 0;

    // join back data here
    for(const auto& prime : prime_struct_array) {
        joined_prime_arrays.insert(joined_prime_arrays.end(), prime.is_prime_array.begin(), prime.is_prime_array.end());
        joined_total_primes += prime.total_primes;
        joined_sum_of_primes += prime.sum_of_primes;
    }

    std::vector<unsigned int> ten_largest_primes_ascending;
    ten_largest_primes_ascending.reserve(10);

    get_ten_largest_primes_ascending(n, joined_prime_arrays, ten_largest_primes_ascending);

    auto stop = std::chrono::high_resolution_clock::now();

    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    save_to_file(execution_time, joined_total_primes, joined_sum_of_primes, ten_largest_primes_ascending);

    return 0;
}