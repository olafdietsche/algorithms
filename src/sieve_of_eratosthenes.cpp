#include <cmath>
#include <cstddef>
#include <vector>

std::vector<bool> sieve_of_eratosthenes(size_t n)
{
	// determine all primes [2,n)
	std::vector<bool> primes(n, true);
	primes[0] = primes[1] = false;
	unsigned long m = sqrt(n);
	for (unsigned long i = 2; i <= m; ++i) {
		if (primes[i]) {
			for (unsigned long j = i * i; j < n; j += i)
				primes[j] = false;
		}
	}

	return primes;
}

template<typename I = unsigned long> std::vector<I> prime_numbers(const std::vector<bool> &primes)
{
	std::vector<I> numbers;
	for (auto i = primes.begin(); i != primes.end(); ++i) {
		if (*i)
			numbers.push_back(std::distance(primes.begin(), i));
	}

	return numbers;
}
