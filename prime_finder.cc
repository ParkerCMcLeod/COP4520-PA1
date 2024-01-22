/*
COP4520-24Spring 0V01: Concept of Parallel and Distributed Processing
Programming Assignment 1
Instructor: Juan Parra
Due date: Friday, January 26th by 11:59 PM
*/

#include <iostream>
#include <fstream>
#include <vector>

// C++11 quirk only allows constexpr f(x)s to have a return statement in the body
constexpr int pow(int base, int exp) {
    return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

void save_to_file(double execution_time, int total_primes, long long sum_of_primes, std::vector<int>& ten_largest_primes_ascending) {
    std::ofstream outFile("primes.txt");
    if (outFile.is_open()) {
        outFile << execution_time << " " << total_primes << " " << sum_of_primes << std::endl;

        for(int i=0; i<ten_largest_primes_ascending.size(); i++)
            outFile << ten_largest_primes_ascending[i] << " ";

        outFile.close();
    } else {
        std::cerr << "Error opening primes.txt." << std::endl;
    }
}

int main() {
    constexpr int i = pow(10, 8); // compile-time calculation of 10^8

    double execution_time = {};

    int total_primes = {};
    
    unsigned long long sum_of_primes = {}; // guranteed to be at least 2^64 - 1 in C++11

    std::vector<int> ten_largest_primes_ascending;
    ten_largest_primes_ascending.reserve(10);

    save_to_file(execution_time, total_primes, sum_of_primes, ten_largest_primes_ascending);

    return 0;
}