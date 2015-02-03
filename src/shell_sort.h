// -*- mode: c++ -*-
// Copyright (c) 2014 Olaf Dietsche

#ifndef __shell_sort_h_included__
#define __shell_sort_h_included__

#include <functional>
#include <iterator>
#include <utility>

template<typename I, typename T = typename std::iterator_traits<I>::value_type, typename C = std::less<T> > void shell_sort(I first, I last, C cmp = C())
{
	size_t n = std::distance(first, last), h = 1;
	do {
		h = h * 3 + 1;
	} while (h < n);

	T t;
	do {
		h /= 3;
		for (auto i = first + h; i != last; ++i) {
			auto j = i;
			t = std::move(*j);
			for (; std::distance(first, j) >= h && cmp(t, *(j - h)); j -= h)
				*j = std::move(*(j - h));

			*j = std::move(t);
		}
	} while (h > 1);
}

#endif
