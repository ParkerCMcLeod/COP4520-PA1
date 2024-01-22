Windows Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc
    Execution: prime_finder
    Both: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc && prime_finder 100000000

Sources:

    https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve

Output:

    <execution time in ms> <total number of primes found> <sum of all primes found>
    <top ten maximum primes, listed in order from lowest to highest>

Notes:

    Why Segmented Sieve over Sieve of Eratosthenes:

        Pros:

            Requires less memory because it only stores primes up to the sqrt root 10^8.
            Easily parallelized by selecting L and R.

        Cons:
        
            Harder to implement espicially with parallelization.