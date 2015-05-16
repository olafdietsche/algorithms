// -*- mode: c++ -*-
// Copyright (c) 2014 Olaf Dietsche

#ifndef __quick_sort_h_included__
#define __quick_sort_h_included__

#include "middle_value.h"
#include <algorithm>
#include <functional>

template<typename I, typename T, typename C> I quicksort_partition(I first, I last, C cmp)
{
	auto middle = first + (last - first) / 2;
	--last;
	T pivot = middle_value(*first, *middle, *last);

	while (first < last) {
		while (first != last && cmp(*first, pivot))
			++first;

		while (first != last && cmp(pivot, *last))
			--last;

		if (first != last)
			std::iter_swap(first, last);
	}

	return first;
}

template<typename I, typename T = typename std::iterator_traits<I>::value_type, typename C = std::less<T>> void quick_sort(I first, I last, C cmp = C())
{
	if (last - first > 1) {
		I i = quicksort_partition<I, T, C>(first, last, cmp);
		quick_sort(first, i, cmp);
		quick_sort(i + 1, last, cmp);
	}
}

#endif
