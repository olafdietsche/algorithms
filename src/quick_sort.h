// -*- mode: c++ -*-
// Copyright (c) 2014 Olaf Dietsche

#ifndef __quick_sort_h_included__
#define __quick_sort_h_included__

#include <algorithm>

template<typename I, typename T, typename C> I quicksort_partition(I first, I last, C cmp)
{
	--last;

	// sort first, middle and last element
	auto middle = first + (last - first) / 2;
	if (cmp(*middle, *first))
		std::iter_swap(first, middle);

	if (cmp(*last, *middle))
		std::iter_swap(last, middle);

	if (cmp(*middle, *first))
		std::iter_swap(first, middle);

	T pivot = *middle;

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
