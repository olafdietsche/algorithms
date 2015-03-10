// -*- mode: c++ -*-
#ifndef __middle_h_included__
#define __middle_h_included__

// Copyright (c) 2015 Olaf Dietsche

/**
 * Find the middle value of three values.
 */

template<typename T> T middle(T a, T b, T c)
{
	if (a < b) {
		if (b < c)
			return b;

		if (a < c)
			return c;

		return a;
	} else {
		if (a < c)
			return a;

		if (c < b)
			return b;

		return c;
	}
}

template<typename C, typename I> I middle(C v, I a, I b, I c)
{
	if (v[a] < v[b]) {
		if (v[b] < v[c])
			return b;

		if (v[a] < v[c])
			return c;

		return a;
	} else {
		if (v[a] < v[c])
			return a;

		if (v[c] < v[b])
			return b;

		return c;
	}
}

#endif
