// -*- mode: c++ -*-
// Copyright (c) 2015 Olaf Dietsche

#ifndef __gcd_h_included__
#define __gcd_h_included__

// Euclid's algorithm for computing the greatest common divisor

template<typename I> I gcd(I a, I b)
{
	while (a > 0 && b > 0) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}

	return a == 0 ? b : a;
}

#endif
