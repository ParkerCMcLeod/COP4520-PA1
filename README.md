Windows Command Prompt Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc
    Execution: prime_finder
    Unified: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc && prime_finder 100000000

Linux Bash Shell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc
    Execution: ./prime_finder
    Unified: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc && ./prime_finder 100000000

PowerShell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc
    Execution: .\prime_finder
    Unified: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc; if ($?) { .\prime_finder 100000000 }

Output Formatting:

    <execution time in ms> <total number of primes found> <sum of all primes found>
    <top ten maximum primes, listed in order from lowest to highest>

Proof of Correctness: 

    Verified correct final ten primes were printed via http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
    Verified my Sieve of Eratosthenes single threaded application results matched Mutithreaded Segmented Sieve
    Made sure to avoid all potential race conditions by making all resources independent per thread.
    Verified results of the number of primes and sum by comparing to python3 implementation found here: https://www.geeksforgeeks.org/sum-of-all-the-prime-numbers-in-a-given-range/

Statement:

    In seeking the best algorithm, the Sieve of Eratosthenes emerged as a top recommendation for efficiently generating prime numbers within my calculation range. I chose its segmented variation for significant memory savings, reducing usage by sqrt(n). Its adaptability for multithreading further cemented my choice. Each thread processed a specific number subset, determined by dividing n by the number of threads (n/num_threads). With preallocated data structures, threads operated independently, avoiding race conditions. After completing their tasks, the threads' outputs—prime boolean arrays and count/sum totals—were merged into a unified dataset. The final step involved consolidating counts/sums and reverse parsing the prime array to extract the first 10 primes in descending order, which were then printed in reverse to negate the need for re-sorting. More on this technique can be found at https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve.


Experimental Evaluations:

    Initially, I implemented the standard sieve using a single thread. Subsequently, I progressed to the segmented sieve, and then to a multithreaded version. During these stages, I experimented with various optimization techniques, including preallocation, sorting, reference passing, and the selection of appropriate data structures for thread communication. Bool arrays proved to be the most efficient in terms of both speed and size, occupying just one byte each. To further enhance efficiency, I utilized std::vec, prioritizing minimal copying and preallocating memory to circumvent the need for resizing. This strucutre also allowed for me to break up and finally combine each thread's individual results.