// -*- mode: c++ -*-
#ifndef __fibonacci_h_included__
#define __fibonacci_h_included__

// Copyright (c) 2015 Olaf Dietsche

template<typename T> T fibonacci_recursive(T n) 
{
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

template<typename T> T fibonacci_iterative(T n) 
{
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	T f0 = 0, f1 = 1, fn = f1 + f0;
	for (T i = 2; i < n; ++i) {
		f0 = f1;
		f1 = fn;
		fn = f1 + f0;
	}

	return fn;
}

#endif
