Windows Command Prompt Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc
    Execution: prime_finder
    Unified: g++ -std=c++11 -pthread -o prime_finder prime_finder.cc && prime_finder 100000000

Output Formatting:

    <execution time in ms> <total number of primes found> <sum of all primes found>
    <top ten maximum primes, listed in order from lowest to highest>

Proof of Correctness: 

    Verified correct final ten primes were printed via http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
    Verified Sieve of Eratosthenes single threaded application results matched Mutithreaded Segmented Sieve 
    Verified results of the number of primes and sum by comparing to python3 implementation found here: https://www.geeksforgeeks.org/sum-of-all-the-prime-numbers-in-a-given-range/

Statement:

    When exploring the best algorithm for my purpose, I found that the Sieve of Eratosthenes was frequently recommended. Renowned for its efficiency in generating prime numbers within my specific calculation range, it stood out as an optimal solution. Delving deeper, I opted for the segmented sieve variation. This approach significantly reduced memory usage, scaling down by the square root of n. Moreover, its structure lent itself well to conversion into a multithreaded application, further enhancing its effectiveness. For more details on this technique, see the Wikipedia's segment on the Segmented Sieve of Eratosthenes https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve.