#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cmath>
#include <type_traits>
#include <limits>
#include <cstdint>

class Math {
public:
	// Return the biggest element in a non-empty vector
	template<typename T>
	static inline T showBiggestFromVector(const std::vector<T>& listOfNr) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		if (listOfNr.empty()) throw std::invalid_argument("listOfNr must not be empty");
		return *std::max_element(listOfNr.begin(), listOfNr.end());
	}

	// Return the biggest of two numbers
	template<typename T>
	static inline T showBiggestFromTwo(T a, T b) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		return (a > b) ? a : b;
	}

	// Return the lowest element in a non-empty vector
	template<typename T>
	static inline T showLowestFromVector(const std::vector<T>& listOfNr) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		if (listOfNr.empty()) throw std::invalid_argument("listOfNr must not be empty");
		return *std::min_element(listOfNr.begin(), listOfNr.end());
	}

	// Return the lowest of two numbers
	template<typename T>
	static inline T showLowestFromTwo(T a, T b) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		return (a < b) ? a : b;
	}



	// Average as double (0.0 for empty container)
	template<typename T>
	static inline double average(const std::vector<T>& listOfNr) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		if (listOfNr.empty()) return 0.0;
		return static_cast<double>(sum(listOfNr)) / static_cast<double>(listOfNr.size());
	}

	// Median as double (works for odd/even sizes)
	template<typename T>
	static inline double median(std::vector<T> listOfNr) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		if (listOfNr.empty()) throw std::invalid_argument("listOfNr must not be empty");
		std::sort(listOfNr.begin(), listOfNr.end());
		size_t n = listOfNr.size();
		if (n % 2 == 1) {
			return static_cast<double>(listOfNr[n / 2]);
		} else {
			return (static_cast<double>(listOfNr[n / 2 - 1]) + static_cast<double>(listOfNr[n / 2])) / 2.0;
		}
	}

	// Clamp value into [lo, hi] (if lo > hi they are swapped)
	template<typename T>
	static inline T clamp(T value, T lo, T hi) {
		static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
		if (lo > hi) std::swap(lo, hi);
		if (value < lo) return lo;
		if (value > hi) return hi;
		return value;
	}

	// Greatest common divisor (works for signed/unsigned integers)
	template<typename T>
	static inline T greatestCommonDivizor(T a, T b) {
		static_assert(std::is_integral<T>::value, "gcd requires integral types");
		using UT = typename std::make_unsigned<T>::type;
		UT ua = static_cast<UT>(a < 0 ? -a : a);
		UT ub = static_cast<UT>(b < 0 ? -b : b);
		while (ub != 0) {
			UT r = ua % ub;
			ua = ub;
			ub = r;
		}
		return static_cast<T>(ua);
	}
)
	template<typename T>
	static inline T lcm(T a, T b) {
		static_assert(std::is_integral<T>::value, "lcm requires integral types");
		if (a == 0 || b == 0) return T(0);
		T g = gcd(a, b);
		// Prevent overflow by using division first when possible
		return static_cast<T>((static_cast<long long>(a) / static_cast<long long>(g)) * static_cast<long long>(b));
	}

	static inline unsigned long long factorial(unsigned int n) {
		unsigned long long result = 1ULL;
		for (unsigned int i = 2; i <= n; ++i) result *= i;
		return result;
	}
};